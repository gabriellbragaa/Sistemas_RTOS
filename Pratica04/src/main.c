#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include <stdio.h>


#define ADC_PIN 26 // adc 0
#define LED_AZUL 18
#define LED_AMAR 17
#define LED_VERM 16




QueueHandle_t adcQueue;


void adcReadTask(void *params) { // task que ira manipular o led
                                // essa task espera um elemento do QUEUE
                                // quando receber o elemento, deve acionar o led


   adc_init();
   adc_gpio_init(ADC_PIN);
   adc_select_input(0);


   float voltage;
   while (1) {
       uint16_t resultado = adc_read();
       voltage = resultado * 3.3f / (1 << 12);
       // toda vez que adcqueue é lido, o valor voltage é enfileirado
       // coloca na queue
       xQueueSend(adcQueue, &voltage, portMAX_DELAY);
       vTaskDelay(pdMS_TO_TICKS(300));
       printf("ADC: %d, Voltage: %.2f V\n", resultado, voltage);
      
       // 0 - 4095




   }
}


void ledControlTask(void *params) {
   gpio_init(LED_AZUL);
   gpio_init(LED_AMAR);
   gpio_init(LED_VERM);
   gpio_set_dir(LED_AZUL, GPIO_OUT);
   gpio_set_dir(LED_AMAR, GPIO_OUT);
   gpio_set_dir(LED_VERM, GPIO_OUT);


   float voltage;
  
   // recebimento da queue
   // retira da queue
   while (1) {
       if (xQueueReceive(adcQueue, &voltage, portMAX_DELAY)) {
           gpio_put(LED_AZUL, voltage > 2.0);
           gpio_put(LED_AMAR, voltage <= 2.0 && voltage >= 1.0);
           gpio_put(LED_VERM, voltage < 1.0);
          
       }
   }
}


int main() {
   stdio_init_all();
  
   adcQueue = xQueueCreate(5, sizeof(float));
   xTaskCreate(adcReadTask, "ADC", 256, NULL, 1, NULL);
   xTaskCreate(ledControlTask, "LED", 256, NULL, 1, NULL);
   vTaskStartScheduler();
   while (1) {}
}





