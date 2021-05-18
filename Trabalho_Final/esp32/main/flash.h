#ifndef FLASH_H
#define FLASH_H

#include <stdio.h>
#include <string.h>
#include "nvs_flash.h"
#include "esp_system.h"
#include "esp_log.h"

#define str_size 40

int32_t le_int_nvs(char * chave);
char * le_string_nvs(char * chave);
void grava_int_nvs(int32_t valor, char * chave);
void grava_string_nvs(char * valor, char * chave);
void inicia_nvs();
void deletaDispositivo(char * chaveC, char * chaveR);
#endif
