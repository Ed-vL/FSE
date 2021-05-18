#ifndef GPIO_H
#define GPIO_H

#include <stdio.h>
#include <string.h>
#include "driver/gpio.h"
#include "esp_system.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "aux.h"

#define str_size 40

void initGpio();
static void IRAM_ATTR gpio_isr_handler(void *args);
void toggleLED();
#endif
