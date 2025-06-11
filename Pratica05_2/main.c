#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "queue.h"
#include <stdio.h>


#define BUTTON_PIN 15
#define LED_PIN 16

uint botao = 0;


SemaphoreHandle_t semaphore;
QueueHandle_t led_queue;

typedef enum {
    LED_TOGGLE 
} led_command_t;


void button_task(void *pvParameters) {
    (void)pvParameters;

    while (1) {
        if ((xSemaphoreTake(semaphore, portMAX_DELAY) == pdTRUE) && botao) {
            printf("Semáforo consumido pelo botão\n");
            led_command_t command = LED_TOGGLE;
            xQueueSend(led_queue, &command, portMAX_DELAY);
            vTaskDelay(pdMS_TO_TICKS(500));

            xSemaphoreGive(semaphore);
            printf("Semáforo liberado pelo botão\n");
            botao = !botao;
        }
    }
}


void led_task(void *pvParameters) {
    (void)pvParameters;

    led_command_t command;
    while (1) {
        if (xQueueReceive(led_queue, &command, portMAX_DELAY) == pdTRUE) {
            if (command == LED_TOGGLE) {
                gpio_put(LED_PIN, !gpio_get(LED_PIN));
                printf("LED alternado\n");
            }
        }
    }
}

// Tarefa para testar o semáforo
void semaphore_test_task(void *pvParameteres) {

     // UBaseType_t contador = 0;
    while (1) {
        if (xSemaphoreTake(semaphore, portMAX_DELAY) == pdTRUE) {
            printf("Semáforo disponível \n");
            vTaskDelay(750);
           // contador++;
           // printf("recurso: %d\n", contador);
            xSemaphoreGive(semaphore);
        } else {
            printf("Semáforo ocupado \n");
            vTaskDelay(750);
        }
    }
}



void button_isr(uint gpio, uint32_t events) {
    BaseType_t higherPriorityTaskWoken = pdFALSE;
    xSemaphoreGiveFromISR(semaphore, &higherPriorityTaskWoken);
    portYIELD_FROM_ISR(higherPriorityTaskWoken);
    botao = !botao;
}


void setup_button_interrupt(void) {
    gpio_set_irq_enabled_with_callback(BUTTON_PIN, GPIO_IRQ_EDGE_RISE, true, button_isr);
}


int main() {
   
    stdio_init_all();
    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_down(BUTTON_PIN); 
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    // Criação de semáforo contador (capacidade 2, valor inicial 0)
    semaphore = xSemaphoreCreateCounting(2, 0);
    if (semaphore == NULL) {
        printf("Erro ao criar o semáforo do botão\n");
        return -1;
    }

    // Criação da fila para comandos de LED
    led_queue = xQueueCreate(10, sizeof(led_command_t));
    if (led_queue == NULL) {
        printf("Erro ao criar a fila do LED\n");
        return -1;
    }

    
    xTaskCreate(button_task, "ButtonTask", 256, NULL, 1, NULL);
    xTaskCreate(led_task, "LedTask", 256, NULL, 1, NULL);
    xTaskCreate(semaphore_test_task, "SemaphoreTestTask", 256, NULL, 1, NULL);
 


    // Configuração da interrupção do botão
    setup_button_interrupt();

   
    vTaskStartScheduler();

    for (;;) {}
    return 0;
}
