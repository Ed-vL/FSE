#include "flash.h"

void inicia_nvs(){
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
      ESP_ERROR_CHECK(nvs_flash_erase());
      ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);
}

void grava_string_nvs(char * valor, char * chave)
{
    nvs_handle particao_padrao_handle;

    esp_err_t res_nvs = nvs_open("armazenamento", NVS_READWRITE, &particao_padrao_handle);
   
    if(res_nvs == ESP_ERR_NVS_NOT_FOUND)
    {
        ESP_LOGE("NVS", "Namespace: armazenamento, não encontrado");
    }

    esp_err_t res = nvs_set_str(particao_padrao_handle, chave, valor);
    if(res != ESP_OK)
    {
        ESP_LOGE("NVS", "Não foi possível escrever no NVS (%s)", esp_err_to_name(res));
    }
    nvs_commit(particao_padrao_handle);
    nvs_close(particao_padrao_handle);
}

void grava_int_nvs(int32_t valor, char * chave)
{
    nvs_handle particao_padrao_handle;

    esp_err_t res_nvs = nvs_open("armazenamento", NVS_READWRITE, &particao_padrao_handle);
   
    if(res_nvs == ESP_ERR_NVS_NOT_FOUND)
    {
        ESP_LOGE("NVS", "Namespace: armazenamento, não encontrado");
    }

    esp_err_t res = nvs_set_i32(particao_padrao_handle, chave, valor);
    if(res != ESP_OK)
    {
        ESP_LOGE("NVS", "Não foi possível escrever no NVS (%s)", esp_err_to_name(res));
    }
    nvs_commit(particao_padrao_handle);
    nvs_close(particao_padrao_handle);
}

int32_t le_int_nvs(char * chave)
{

    int32_t valor = 0;
    nvs_handle particao_padrao_handle;
    printf("Chave: %s\n",chave);
    esp_err_t res_nvs = nvs_open("armazenamento", NVS_READONLY, &particao_padrao_handle);

    if(res_nvs == ESP_ERR_NVS_NOT_FOUND)
    {
        ESP_LOGE("NVS_Int", "Namespace: armazenamento, não encontrado");
    }
    else
    {
        esp_err_t res = nvs_get_i32(particao_padrao_handle, chave, &valor);

        switch (res)
        {
        case ESP_OK:
            printf("Valor armazenado: %d\n", valor);
            break;
        case ESP_ERR_NOT_FOUND:
            ESP_LOGE("NVS_Int", "Valor não encontrado");
            return -1;
        default:
            ESP_LOGE("NVS_Int", "Erro ao acessar o NVS (%s)", esp_err_to_name(res));
            return -1;
            break;
        }

        nvs_close(particao_padrao_handle);
    }
    return valor;
}

char * le_string_nvs(char * chave)
{

    size_t t;
    char * valor = malloc(str_size);
    nvs_handle particao_padrao_handle;
    
    esp_err_t res_nvs = nvs_open("armazenamento", NVS_READONLY, &particao_padrao_handle);

    if(res_nvs == ESP_ERR_NVS_NOT_FOUND)
    {
        ESP_LOGE("NVS_String", "Namespace: armazenamento, não encontrado");
    }
    else
    {
        esp_err_t res = nvs_get_str(particao_padrao_handle, chave, valor, &t);

        switch (res)
        {
        case ESP_OK:
            printf("Valor armazenado: %s\n", valor);
            break;
        case ESP_ERR_NOT_FOUND:
            ESP_LOGE("NVS_String", "Valor não encontrado");
            return "Err";
        default:
            ESP_LOGE("NVS_String", "Erro ao acessar o NVS (%s)", esp_err_to_name(res));
            return "Err";
            break;
        }

        nvs_close(particao_padrao_handle);
    }
    return valor;
}

void deletaDispositivo(char * chaveC, char * chaveR)
{
    grava_string_nvs("",chaveC);
    grava_int_nvs(0,chaveR);
}