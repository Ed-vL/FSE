#include "aux.h"

void sendInterrupt(char * message)
{
  char * string = NULL;
  cJSON * tipo = NULL;
  cJSON * evento = NULL;
  cJSON *monitor = cJSON_CreateObject();
  char * id = malloc(sizeof(char)*20);
  id = Pega_macAddress();
  tipo = cJSON_CreateString(id);
  evento = cJSON_CreateString(message);
  cJSON_AddItemToObject(monitor, "id", tipo);
  cJSON_AddItemToObject(monitor, "estado", evento);
  string = cJSON_Print(monitor);
    char * topico = malloc(sizeof(char)*50);
    topico = Pega_topico("estado");
    printf("topic: %s",topico);
    mqtt_envia_mensagem(topico, string);
}

void dhtPush(void * params)
{
  char * stringU = NULL;
  cJSON * tipoU = NULL;
  cJSON * valorU = NULL;
  cJSON * monitorU = cJSON_CreateObject();

  char * stringT = NULL;
  cJSON * valorT = NULL;
  cJSON * tipoT = NULL;
  cJSON * monitorT = cJSON_CreateObject();

  char * topicoU = malloc(sizeof(char)*50);
  

  char * topicoT = malloc(sizeof(char)*50);
  char * topic = malloc(sizeof(char)*50);
 
  tipoU = cJSON_CreateString("umidade");
  tipoT = cJSON_CreateString("temperatura");
  printf("Esperando MQTT\n");
  if(xSemaphoreTake(conexaoMQTTSemaphore, portMAX_DELAY)){
    xSemaphoreGive(conexaoMQTTSemaphore);
    xSemaphoreTake(cadastro_Semaphore, portMAX_DELAY);
    topic = Pega_topico("saida");
    mqtt_subscriber(topic);
    topicoU = Pega_topico("umidade");
    topicoT = Pega_topico("temperatura");
    while (true)
    {
      struct dht11_reading dht = DHT11_read();
      
      valorU = cJSON_CreateNumber(dht.humidity);
      cJSON_AddItemToObject(monitorU, "tipo", tipoU);
      cJSON_AddItemToObject(monitorU, "valor", valorU);
      stringU = cJSON_Print(monitorU);
      mqtt_envia_mensagem(topicoU,stringU);
      printf("Umidade: %s", stringU);
      valorT = cJSON_CreateNumber(dht.temperature);
      cJSON_AddItemToObject(monitorT, "tipo", tipoT);
      cJSON_AddItemToObject(monitorT, "valor", valorT);
      stringT = cJSON_Print(monitorT);
      mqtt_envia_mensagem(topicoT,stringT);
      printf("Temperatura: %s", stringT);
      vTaskDelay(freq / portTICK_PERIOD_MS);
    }
    
  }

}