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
#include "gpio.h"
#include "dht11.h"
#include "esp_sleep.h"
#include <unistd.h>
#include "driver/rtc_io.h"

xSemaphoreHandle conexaoWifiSemaphore;
xSemaphoreHandle conexaoMQTTSemaphore;
xSemaphoreHandle cadastro_Semaphore;

#define ESP_MODE CONFIG_ESP_MODE_BATTERY

int32_t estaRegistrado;
RTC_DATA_ATTR int Acordou = 0;

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
    } else {
      xSemaphoreGive(cadastro_Semaphore);   
    }
     xSemaphoreGive(conexaoMQTTSemaphore);   
  }
}

void app_main(void)
{
  int battery = 0;
  #ifdef CONFIG_ESP_MODE_BATTERY
      battery = 1;
  #endif
  if(Acordou){
    battery = 0;
  }
    inicia_nvs();
    if(!battery){
      DHT11_init(GPIO_NUM_4);
      initGpio();
    }
    conexaoWifiSemaphore = xSemaphoreCreateBinary();
    conexaoMQTTSemaphore = xSemaphoreCreateBinary();
    cadastro_Semaphore = xSemaphoreCreateBinary();
    wifi_start();
    xTaskCreate(&conectadoWifi, "Conexão ao MQTT", 4096, NULL, 1, NULL);
    verificaDispositivo();
    if(!battery)
      xTaskCreate(&dhtPush,"Monitoramento",4096,NULL,1,NULL);
    else {
        rtc_gpio_pullup_en(BOTAO);
        rtc_gpio_pulldown_dis(BOTAO);
        esp_sleep_enable_ext0_wakeup(BOTAO, 0);
        printf("Entrando em modo Bateria\n");
        Acordou = 1;
        esp_deep_sleep_start();
    }

}
