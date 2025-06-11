#include "FreeRTOS.h"
#include "task.h"
#include "pico/stdlib.h"
#include <stdio.h>


// contar ciclos de idle
volatile uint32_t idle_tick_counter = 0;


void task_blink_16(void *pvParameters) {
    (void)pvParameters;
    while (1) {
        gpio_put(16, 1);
        vTaskDelay(pdMS_TO_TICKS(50));

        gpio_put(16, 0);
        vTaskDelay(pdMS_TO_TICKS(50));
        
       
    }
}

void task_blink_15(void *pvParameters) {
    (void)pvParameters;
    while (1) {
        gpio_put(15, 1);
        vTaskDelay(pdMS_TO_TICKS(50));

        gpio_put(15, 0);
        vTaskDelay(pdMS_TO_TICKS(50));
        
    }
}
/*
void task_blink_three_times(void *pvParameters) {
    (void)pvParameters;

    for (int i = 0; i < 3; i++) {
        gpio_put(25, 1);
        printf("LED no pino 25 ligado (pisca %d/3)\n", i+1);
        vTaskDelay(pdMS_TO_TICKS(500));

        gpio_put(25, 0);
        printf("LED no pino 25 desligado (pisca %d/3)\n", i+1);
        vTaskDelay(pdMS_TO_TICKS(500));
    }

    vTaskDelete(NULL);
} */

    // incrementa idle_tick_counter sempre que a CPU está ociosa
void vApplicationIdleHook(void) {
    unsigned long int tick = xTaskGetTickCount();
    
    // Aguarda pelo próximo tick certificar que ocorreu um ciclo
    while (xTaskGetTickCount() == tick) {} 
    idle_tick_counter++;
}

void taskCPUUsage(void *pvParameters) {
    unsigned long int idle_tick_last = 0, ticks;
    (void)pvParameters;

    for (;;) {
        
        vTaskDelay(pdMS_TO_TICKS(2000));

        // Calcula ticks de idle por segundo
        if (idle_tick_counter > idle_tick_last)
            ticks = idle_tick_counter - idle_tick_last; // ticks ociosos
        else
            ticks = 0xFFFFFFFF - idle_tick_last + idle_tick_counter;


        ticks /= 4;
        
        // Imprime ticks de idle por segundo
        printf("%lu idle ticks per second (out of %lu)\n", ticks, configTICK_RATE_HZ); 

        // 1000hz = 1tick -> 1ms

        
        // Calcula e imprime uso de CPU
        ticks = (configTICK_RATE_HZ - ticks) * 100 / configTICK_RATE_HZ;
        printf("CPU usage: %u%%\n", ticks);
    

        idle_tick_last = idle_tick_counter;
    }
}



int main() {
    stdio_init_all();


    gpio_init(16);
    gpio_set_dir(16, GPIO_OUT);

    gpio_init(15);
    gpio_set_dir(15, GPIO_OUT);

    // xTaskCreate(task_blink_three_times, "print", 256, NULL, 1, NULL);
    xTaskCreate(task_blink_16, "Blink 16", 256, NULL, 1, NULL);
    xTaskCreate(task_blink_15, "Blink 15", 256, NULL, 1, NULL);
    xTaskCreate(taskCPUUsage, "CPU Usage", 256, NULL, 2, NULL);
    

    // Inicia o escalonador
    vTaskStartScheduler();


    for (;;);
    return 0;
}
