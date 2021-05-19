#ifndef AUX_H
#define AUX_H

#include "mqtt.h"
#include "cJSON.h"
#include "dht11.h"
#include "freertos/semphr.h"
#define freq 2000

extern xSemaphoreHandle conexaoMQTTSemaphore;
extern xSemaphoreHandle cadastro_Semaphore;

void sendInterrupt(char * message);
void dhtPush(void * params);
#endif
