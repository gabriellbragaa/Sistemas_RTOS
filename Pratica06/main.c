#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include <stdio.h>
#include "hardware/adc.h"
#include <queue.h>


#define ADC_NUM 0
#define ADC_PIN (26 + ADC_NUM )

SemaphoreHandle_t mutex;

// estrutura global

typedef struct {
    int16_t potenciometro;

} AccelerometerData;

AccelerometerData accelData;

void lendoAccele( AccelerometerData* data){
    data-> potenciometro = adc_read();
    
}



void vTaskLerPotenciometro(void *pvParameters) {

    for(;;) {
        if(xSemaphoreTake(mutex, portMAX_DELAY)) {
            
            //  Leitura do Potenciometro
            lendoAccele(&accelData);
            printf("lendo..\n");
            
            xSemaphoreGive(mutex);
        }
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}


void vTaskMostrarConteudo(void *pvParameters) {

    for(;;)
     {
        if(xSemaphoreTake(mutex, portMAX_DELAY)) {
            
             printf("Potenciometro: %d\n", accelData.potenciometro);   
            
            xSemaphoreGive(mutex);
        }
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}



int main() {
    
    stdio_init_all();


    // Potentiometer Config
    adc_init();
    adc_gpio_init(ADC_PIN);
    adc_select_input(ADC_NUM);
    
    // Create a Mutex
    mutex = xSemaphoreCreateMutex();

    
    xTaskCreate(vTaskLerPotenciometro, "Potenciometro", 256, NULL, 2, NULL);
    xTaskCreate(vTaskMostrarConteudo, "dados", 256, NULL, 1, NULL);

    
    vTaskStartScheduler();

}
