#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include <stdio.h>

#define ADC_PIN     26 // ADC0
#define LED_AZUL    18
#define LED_AMAR    17
#define LED_VERM    16
#define BUTTON_PIN  15
#define LED_INTERNO 25

TaskHandle_t T1, T2, T3, T4;
QueueHandle_t adcQueue, buttonQueue;


void gpio_button_irq(uint gpio, uint32_t events) {
    BaseType_t x = pdFALSE;
    uint8_t msg = 1;
    xQueueSendFromISR(buttonQueue, &msg, &x);
    portYIELD_FROM_ISR(x);
}


void ledButtonTask(void *params) {
    uint32_t ledb;
    bool led_state = false;

    gpio_init(LED_INTERNO);
    gpio_set_dir(LED_INTERNO, GPIO_OUT);
    gpio_put(LED_INTERNO, led_state);

    for (;;) {
        if (xQueueReceive(buttonQueue, &ledb, portMAX_DELAY) == pdTRUE) {
            
            led_state = !led_state;
            gpio_put(LED_INTERNO, led_state);
            printf("Botão pressionado: %s\n", led_state ? "ON" : "OFF");

            
            vTaskDelay(pdMS_TO_TICKS(200));

            while (uxQueueMessagesWaiting(buttonQueue) > 0) {
                xQueueReceive(buttonQueue, &ledb, 0);
            }
        }
    }
}
void adcReadTask(void *params) {
    adc_init();
    adc_gpio_init(ADC_PIN);
    adc_select_input(0);

    float voltage;
    for (;;) {
        uint16_t resultado = adc_read();
        voltage = resultado * 3.3f / (1 << 12);
        xQueueSend(adcQueue, &voltage, portMAX_DELAY);
        printf("ADC: %d, Voltage: %.2f V\n", resultado, voltage);
        vTaskDelay(pdMS_TO_TICKS(300));
    }
}



void ledControlTask(void *params) {
    float voltage;

    gpio_init(LED_VERM); gpio_set_dir(LED_VERM, GPIO_OUT);
    gpio_init(LED_AMAR); gpio_set_dir(LED_AMAR, GPIO_OUT);
    gpio_init(LED_AZUL); gpio_set_dir(LED_AZUL, GPIO_OUT);

    for (;;) {
        if (xQueueReceive(adcQueue, &voltage, portMAX_DELAY)) {
            gpio_put(LED_VERM, voltage < 1.0f);
            gpio_put(LED_AMAR, voltage >= 1.0f && voltage <= 2.0f);
            gpio_put(LED_AZUL, voltage > 2.0f);
            printf("1:%d",voltage < 1.0f);
            printf("2:%d",voltage >= 1.0f && voltage <= 2.0);
            printf("3:%d\n",voltage > 2.0f);
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
    for (;;) vTaskDelay(portMAX_DELAY); 
}

int main() {
    stdio_init_all();
    adcQueue = xQueueCreate(5, sizeof(float));
    buttonQueue = xQueueCreate(5, sizeof(uint8_t));

    
    xTaskCreate(adcReadTask,    "ADC",       256, NULL, 1, NULL);
    xTaskCreate(ledControlTask, "LED_ADC",   256, NULL, 1, NULL);
    xTaskCreate(buttonTask,     "Button",    256, NULL, 1, NULL);  
    xTaskCreate(ledButtonTask,  "LedButton", 256, NULL, 1, NULL);

    vTaskStartScheduler();

   
}