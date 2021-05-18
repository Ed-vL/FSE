#include <stdio.h>
#include <string.h>
#include "nvs_flash.h"
#include "esp_wifi.h"
#include "esp_http_client.h"
#include "esp_log.h"
#include "freertos/semphr.h"
#include "esp_system.h"
#include "esp_event.h"
#include "esp_netif.h"
#include "wifi.h"
#include "http_client.h"
#include "mqtt.h"
#include "flash.h"
#include <unistd.h>

xSemaphoreHandle conexaoWifiSemaphore;
xSemaphoreHandle conexaoMQTTSemaphore;

int32_t estaRegistrado;

void conectadoWifi(void * params)
{

  while(true)
  {
    if(xSemaphoreTake(conexaoWifiSemaphore, portMAX_DELAY))
    {
      mqtt_start();
    }
  }
}

void verificaDispositivo()
{
  estaRegistrado = 0;
  estaRegistrado = le_int_nvs("Registrador");
  if(xSemaphoreTake(conexaoMQTTSemaphore, portMAX_DELAY)){
    if(!estaRegistrado){
      mqtt_register();
      estaRegistrado = 1;
      grava_int_nvs(estaRegistrado, "Registrador");
    }      
  }
}

void app_main(void)
{
    inicia_nvs();
    conexaoWifiSemaphore = xSemaphoreCreateBinary();
    conexaoMQTTSemaphore = xSemaphoreCreateBinary();
    wifi_start();
    xTaskCreate(&conectadoWifi, "Conexão ao MQTT", 4096, NULL, 1, NULL);
    verificaDispositivo();
}
