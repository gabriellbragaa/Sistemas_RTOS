#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include <stdio.h>

#define BUTTON_PIN 15
#define LED_PIN    25

QueueHandle_t buttonQueue;
TaskHandle_t ledTaskHandle;

// Interrupção do botão (envia mensagem para a fila)
void gpio_button_irq(uint gpio, uint32_t events) {
    BaseType_t higher_woken = pdFALSE;
    uint8_t msg = 1; 
    xQueueSendFromISR(buttonQueue, &msg, &higher_woken);
    portYIELD_FROM_ISR(higher_woken);
}


void ledTask(void *params) {
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    uint8_t msg;

    while (1) {
        if (xQueueReceive(buttonQueue, &msg, portMAX_DELAY) == pdPASS) {
            gpio_put(LED_PIN, !gpio_get(LED_PIN)); 
            printf("Botão pressionado! LED: %s\n", gpio_get(LED_PIN) ? "LIGADO" : "DESLIGADO");
        }
    }
}

void buttonTask(void *params) {
    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_down(BUTTON_PIN);
    gpio_set_irq_enabled_with_callback(
        BUTTON_PIN, GPIO_IRQ_EDGE_RISE, true, &gpio_button_irq
    );
    while (1) vTaskDelay(portMAX_DELAY); // Fica em loop sem fazer nada
}

int main() {
    stdio_init_all();
    buttonQueue = xQueueCreate(5, sizeof(uint8_t));

    xTaskCreate(ledTask, "LED_Task", 256, NULL, 1, &ledTaskHandle);
    xTaskCreate(buttonTask, "Button_Task", 256, NULL, 1, NULL);

    vTaskStartScheduler();

    while (1) {}
}