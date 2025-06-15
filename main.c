#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"



// Definição dos pinos
#define LED_RED     11
#define LED_GREEN   12
#define LED_BLUE    13
#define BUZZER_PIN  10
#define BUTTON_A    5
#define BUTTON_B    6

// Handles para as tarefas
TaskHandle_t led_task_handle = NULL;
TaskHandle_t buzzer_task_handle = NULL;


void led_rgb_task(void *pvParameters) {
    gpio_init(LED_RED);
    gpio_init(LED_GREEN);
    gpio_init(LED_BLUE);
    
    gpio_set_dir(LED_RED, GPIO_OUT);
    gpio_set_dir(LED_GREEN, GPIO_OUT);
    gpio_set_dir(LED_BLUE, GPIO_OUT);

    while (true) {
        // Vermelho
        gpio_put(LED_RED, 1);
        gpio_put(LED_GREEN, 0);
        gpio_put(LED_BLUE, 0);
        vTaskDelay(pdMS_TO_TICKS(1000));

        // Verde
        gpio_put(LED_RED, 0);
        gpio_put(LED_GREEN, 1);
        gpio_put(LED_BLUE, 0);
        vTaskDelay(pdMS_TO_TICKS(1000));

        // Azul
        gpio_put(LED_RED, 0);
        gpio_put(LED_GREEN, 0);
        gpio_put(LED_BLUE, 1);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void buzzer_task(void *pvParameters) {
    gpio_init(BUZZER_PIN);
    gpio_set_dir(BUZZER_PIN, GPIO_OUT);

    while (true) {
        gpio_put(BUZZER_PIN, 1);
        vTaskDelay(pdMS_TO_TICKS(100));
        gpio_put(BUZZER_PIN, 0);
        vTaskDelay(pdMS_TO_TICKS(1900)); // Bipe a cada 2 segundos
    }
}

void button_control_task(void *pvParameters) {
    gpio_init(BUTTON_A);
    gpio_init(BUTTON_B);
    
    gpio_set_dir(BUTTON_A, GPIO_IN);
    gpio_set_dir(BUTTON_B, GPIO_IN);
    
    gpio_pull_up(BUTTON_A);
    gpio_pull_up(BUTTON_B);

    while (true) {
        // Controle do LED RGB (Botão A)
        if (!gpio_get(BUTTON_A)) {
            if (eTaskGetState(led_task_handle) == eSuspended) {
                vTaskResume(led_task_handle);
            } else {
                vTaskSuspend(led_task_handle);
            }
            vTaskDelay(pdMS_TO_TICKS(200)); // Debouncing
        }

        // Controle do Buzzer (Botão B)
        if (!gpio_get(BUTTON_B)) {
            if (eTaskGetState(buzzer_task_handle) == eSuspended) {
                vTaskResume(buzzer_task_handle);
            } else {
                vTaskSuspend(buzzer_task_handle);
            }
            vTaskDelay(pdMS_TO_TICKS(200)); // Debouncing
        }

        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

int main() {
    stdio_init_all();

   // Criação das tarefas com prioridades diferentes
    xTaskCreate(led_rgb_task, "LED_RGB_Task", 256, NULL, 1, &led_task_handle);
    xTaskCreate(buzzer_task, "Buzzer_Task", 256, NULL, 1, &buzzer_task_handle);
    xTaskCreate(button_control_task, "Button_Control_Task", 256, NULL, 2, NULL);

    vTaskStartScheduler();

    while(1){};
}