#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "queue.h"
#include <stdio.h>


#define BUTTON_PIN 15
#define LED_PIN 16

uint botão = 0;

SemaphoreHandle_t button_semaphore;
QueueHandle_t led_queue;

typedef enum {
    LED_TOGGLE 
} led_command_t;

void button_task(void *pvParameters) {
    (void)pvParameters;

    while (1) {
        
        if ((xSemaphoreTake(button_semaphore, portMAX_DELAY) == pdTRUE) && botão) {
            printf("Semáforo consumido pela tarefa do botão\n");
            led_command_t command = LED_TOGGLE;
            xQueueSend(led_queue, &command, portMAX_DELAY);

            vTaskDelay(pdMS_TO_TICKS(200));
            xSemaphoreGive(button_semaphore);
            printf("Semáforo liberado pela tarefa do botão\n");
            botão = !botão;
        }
    }
}


void led_task(void *pvParameters) {
    (void)pvParameters;

    led_command_t command;
    while (1) {
        
        if (xQueueReceive(led_queue, &command, portMAX_DELAY) == pdTRUE) {
            //printf("Comando recebido da fila: %d\n",sizeof(command));

            if (command == LED_TOGGLE) {
                gpio_put(LED_PIN, !gpio_get(LED_PIN));
                
            }
        }
    }
}


void semaphore_test(void *pvParameteres) {
	while (1) {
		if (xSemaphoreTake(button_semaphore, portMAX_DELAY) == pdTRUE) { // estado de bloqueio
			printf("Semáforo livre\n");
			vTaskDelay(200);
			xSemaphoreGive(button_semaphore); // desbloquear a tarefa
		
		} else {
			printf("Semáforo bloqueado\n");
			vTaskDelay(200);
		}
	}
}


void button_isr(uint gpio, uint32_t events) {
    BaseType_t higherPriorityTaskWoken = pdFALSE;
    
    xSemaphoreGiveFromISR(button_semaphore, &higherPriorityTaskWoken);
    portYIELD_FROM_ISR(higherPriorityTaskWoken);
    botão = !botão;
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

    // Cria um semáforo binário
    button_semaphore = xSemaphoreCreateBinary(); 
    if (button_semaphore == NULL) {
        printf("Falha ao criar o semáforo do botão\n");
        return -1;
    }

    // Cria uma fila
    led_queue = xQueueCreate(4, sizeof(led_command_t));
    

    
    xTaskCreate(semaphore_test, "Test_Semaphore", 256, NULL, 2, NULL);
    xTaskCreate(button_task, "ButtonTask", 256, NULL, 1, NULL);
    xTaskCreate(led_task,    "LedTask", 256, NULL, 1, NULL);

    // Configura a interrupção do botão
    setup_button_interrupt();

   
    vTaskStartScheduler();

    
}
