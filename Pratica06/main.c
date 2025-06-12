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
uint8_t cont = 0;

// estrutura global

typedef struct {
    int16_t otenciometro;p

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
        vTaskDelay(pdMS_TO_TICKS(50));
    }
}

void vTaskSimulartest(void *pvParameters) {
    uint8_t cont = 0;
    float voltage =0;

    for (;;) {
        if (xSemaphoreTake(mutex, portMAX_DELAY)) {
            cont++;
            if(accelData.potenciometro < 4095){
            accelData.potenciometro += 3;
            } // somente incrementar para teste
            uint16_t resultado = adc_read();
            voltage = resultado * 3.3f / (1 << 12) ; 
            printf("Recurso [ %d ] Potenciometro %.2fv e ADC: %d\n" , cont , voltage,  accelData.potenciometro);   
            xSemaphoreGive(mutex);
        }
        if(cont > 100){
        vTaskDelete(NULL);
    }
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}


void vTaskMostrarConteudo(void *pvParameters) {
    
    uint8_t cont = 0;
    float voltage = 0;
    uint16_t resultado = adc_read();

    for(;;)
     {

        if(xSemaphoreTake(mutex, portMAX_DELAY)) {
             cont ++;
             uint16_t resultado = adc_read();
             voltage = resultado * 3.3f / (1 << 12) ; 
             printf("Recurso [ %d ] Potenciometro: %.2fv ADC: %d\n", cont , voltage, accelData.potenciometro);   
            
            xSemaphoreGive(mutex);
        }
       
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
    
}



int main() {
    
    stdio_init_all();


    
    adc_init();
    adc_gpio_init(ADC_PIN);
    adc_select_input(ADC_NUM);
    
    // Create a Mutex
    mutex = xSemaphoreCreateMutex();

    
    xTaskCreate(vTaskLerPotenciometro, "Potenciometro", 256, NULL, 2, NULL);
    xTaskCreate(vTaskMostrarConteudo, "dados", 256, NULL, 1, NULL);
    xTaskCreate(vTaskSimulartest, "Simulador", 256, NULL, 1, NULL);

    
    vTaskStartScheduler();

}

/// ACEITO