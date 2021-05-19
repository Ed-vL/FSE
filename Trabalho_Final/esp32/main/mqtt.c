#include "gpio.h"


#define TAG "MQTT"

extern xSemaphoreHandle conexaoMQTTSemaphore;
extern xSemaphoreHandle cadastro_Semaphore;

esp_mqtt_client_handle_t client;

char * Pega_topico(char * tipo)
{
    char * comodo;
    comodo = le_string_nvs("Comodo");
    char * topico  = malloc(sizeof(char) *50);
    sprintf(topico,"fse2020/%s/%s/%s", MATRICULA,comodo,tipo);
    return topico;
}

char* Pega_macAddress()
{
    u_int8_t base_mac_address[6] = {0};
    int size = 20;
    char *mac = malloc(size);
    esp_efuse_mac_get_default(base_mac_address);
    snprintf(
        mac,
        size,
        "%x%x%x%x%x%x",
        base_mac_address[0],
        base_mac_address[1],
        base_mac_address[2],
        base_mac_address[3],
        base_mac_address[4],
        base_mac_address[5]
    );
    return mac;
}

void trataMensagem(char * mensagem)
{
    cJSON *body = cJSON_Parse(mensagem);

    char * tipoMensagem = cJSON_GetObjectItem(body, "Tipo")->valuestring;
    if(!strcmp(tipoMensagem, "Registro")){
        char * comodo = cJSON_GetObjectItem(body, "Comodo")->valuestring;
        grava_string_nvs(comodo, "Comodo");
        xSemaphoreGive(cadastro_Semaphore);
    }
    if(!strcmp(tipoMensagem, "Remover")){
        deletaDispositivo("Comodo","Registrador");
    }
    if(!strcmp(tipoMensagem, "LED")){
        toggleLED();
    }


}

static esp_err_t mqtt_event_handler_cb(esp_mqtt_event_handle_t event)
{    
    switch (event->event_id) {
        case MQTT_EVENT_CONNECTED:
            ESP_LOGI(TAG, "MQTT_EVENT_CONNECTED");
            xSemaphoreGive(conexaoMQTTSemaphore);
            break;
        case MQTT_EVENT_DISCONNECTED:
            ESP_LOGI(TAG, "MQTT_EVENT_DISCONNECTED");
            break;

        case MQTT_EVENT_SUBSCRIBED:
            ESP_LOGI(TAG, "MQTT_EVENT_SUBSCRIBED, msg_id=%d", event->msg_id);
            break;
        case MQTT_EVENT_UNSUBSCRIBED:
            ESP_LOGI(TAG, "MQTT_EVENT_UNSUBSCRIBED, msg_id=%d", event->msg_id);
            break;
        case MQTT_EVENT_PUBLISHED:
            ESP_LOGI(TAG, "MQTT_EVENT_PUBLISHED, msg_id=%d", event->msg_id);
            break;
        case MQTT_EVENT_DATA:
            ESP_LOGI(TAG, "MQTT_EVENT_DATA");
            trataMensagem(event->data);
            break;
        case MQTT_EVENT_ERROR:
            ESP_LOGI(TAG, "MQTT_EVENT_ERROR");
            break;
        default:
            ESP_LOGI(TAG, "Other event id:%d", event->event_id);
            break;
    }
    return ESP_OK;
}

static void mqtt_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data) {
    ESP_LOGD(TAG, "Event dispatched from event loop base=%s, event_id=%d", base, event_id);
    mqtt_event_handler_cb(event_data);
}

void mqtt_subscriber(char * topic){
    int msgid;
    msgid = esp_mqtt_client_subscribe(client, topic, 0);
    ESP_LOGI(TAG, "MQTT_EVENT_SUBSCRIBED, msg_id=%d", msgid);
}

void mqtt_register(){
  char topic[50];
  char * mac_address = Pega_macAddress();
  char * string = NULL;
  cJSON * tipo = NULL;
  cJSON * id = NULL;
  cJSON *monitor = cJSON_CreateObject();
  tipo = cJSON_CreateString("Cadastro");
  id = cJSON_CreateString(mac_address);
  cJSON_AddItemToObject(monitor, "tipo", tipo);
  cJSON_AddItemToObject(monitor, "id", id);
  string = cJSON_Print(monitor);
  sprintf(topic,"fse2020/%s/dispositivos/%s", MATRICULA,mac_address);
  mqtt_envia_mensagem(topic, string);
  mqtt_subscriber(topic);
}

void mqtt_start()
{
    esp_mqtt_client_config_t mqtt_config = {
        .uri = "mqtt://test.mosquitto.org",
    };
    client = esp_mqtt_client_init(&mqtt_config);
    esp_mqtt_client_register_event(client, ESP_EVENT_ANY_ID, mqtt_event_handler, client);
    esp_mqtt_client_start(client);
}

void mqtt_envia_mensagem(char * topico, char * mensagem)
{
    int message_id = esp_mqtt_client_publish(client, topico, mensagem, 0, 1, 0);
    ESP_LOGI(TAG, "Mesnagem enviada, ID: %d", message_id);
}

