#include "FreeRTOS.h"
#include "task.h"
#include "pico/stdlib.h"
#include <stdio.h>


void task_blink_25(void *pvParameters) {
    (void)pvParameters; 

    while (1) {
        gpio_put(25, 1);
        printf("LED no pino 25 ligado\n");
        vTaskDelay(pdMS_TO_TICKS(500));

        gpio_put(25, 0);
        printf("LED no pino 25 desligado\n");
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}


void task_blink_16(void *pvParameters) {
    (void)pvParameters;

    while (1) {
        gpio_put(16, 1);
        printf("LED no pino 16 ligado\n");
        vTaskDelay(pdMS_TO_TICKS(500));

        gpio_put(16, 0);
        printf("LED no pino 16 desligado\n");
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}


void task_blink_15(void *pvParameters) {
    (void)pvParameters;

    while (1) {
        gpio_put(15, 1);
        printf("LED no pino 15 ligado\n");
        vTaskDelay(pdMS_TO_TICKS(500));

        gpio_put(15, 0);
        printf("LED no pino 15 desligado\n");
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}


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
}

int main() {
    stdio_init_all();

    gpio_init(25);
    gpio_set_dir(25, GPIO_OUT);

    gpio_init(16);
    gpio_set_dir(16, GPIO_OUT);

    gpio_init(15);
    gpio_set_dir(15, GPIO_OUT);

    // Cria as tarefas
    
    xTaskCreate(task_blink_16, "Blink 16", 256, NULL, 1, NULL);
    xTaskCreate(task_blink_15, "Blink 15", 256, NULL, 1, NULL);
    xTaskCreate(task_blink_three_times, "Blink 3x", 256, NULL, 1, NULL);

    // escalonador do FREERTOS
    vTaskStartScheduler();

    while (1); 
}
