#include "gpio.h"



xQueueHandle filaDeInterrupcao;

int on;

static void IRAM_ATTR gpio_isr_handler(void *args)
{
  int pino = (int)args;
  xQueueSendFromISR(filaDeInterrupcao, &pino, NULL);
}

void trataInterrupcaoBotao(void *params)
{
  int pino;
  int contador = 0;

  while(true)
  {
    if(xQueueReceive(filaDeInterrupcao, &pino, portMAX_DELAY))
    {
      int estado = gpio_get_level(pino);
      if(estado == 1)
      {
        gpio_isr_handler_remove(pino);
        contador++;
        printf("Os botões foram acionados %d vezes. Botão: %d\n", contador, pino);
        sendInterrupt("Botao acionado");
        vTaskDelay(50 / portTICK_PERIOD_MS);
        gpio_isr_handler_add(pino, gpio_isr_handler, (void *) pino);
      }

    }
  }
}


void initGpio()
{
  on = 0;
  //LED
  gpio_pad_select_gpio(LED);   
  gpio_set_direction(LED, GPIO_MODE_OUTPUT);
  gpio_set_direction(BOTAO, GPIO_MODE_INPUT);
  //BOTAO
  gpio_pulldown_en(BOTAO);
  gpio_pullup_dis(BOTAO);
 
  gpio_set_intr_type(BOTAO, GPIO_INTR_POSEDGE);

  filaDeInterrupcao = xQueueCreate(10, sizeof(int));
  xTaskCreate(trataInterrupcaoBotao, "TrataBotao", 2048, NULL, 1, NULL);

  gpio_install_isr_service(0);
  gpio_isr_handler_add(BOTAO, gpio_isr_handler, (void *) BOTAO);
}

void toggleLED()
{
    gpio_pad_select_gpio(LED);
    if(!on){
        on = 1;
    } else {
        on = 0;
    }
    gpio_set_level(LED, on);
}