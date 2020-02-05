#include <Arduino_FreeRTOS.h>


TaskHandle_t task1handle; //it is xTaskHandle in original FreeRTOS syntax
TaskHandle_t task2handle;//it is xTaskHandle in original FreeRTOS syntax

void Task1(void *pvParameters)  // This is a task.
{
  Serial.begin(9600);
  while (1)
  { Serial.println("Hi ! Im learning FreeRTOs\n");
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }

}

void Task2(void *pvParameters)  // This is a task.
{
  Serial.begin(9600);
  while (1)
  {
    Serial.println("Im suspending task1 for 5 sec\n");
    vTaskSuspend(task1handle);
    vTaskDelay( 5000 / portTICK_PERIOD_MS);
    Serial.println("Im releasing task 1 for 5 second\n");
    vTaskResume(task1handle);
    vTaskDelay( 5000 / portTICK_PERIOD_MS);
  }
}


// the setup function runs once when you press reset or power the board
void setup() {

  // Now set up two tasks to run independently.
  xTaskCreate(
    Task1
    ,  "Blink"   // A name just for humans
    ,  128  // Stack size
    ,  NULL
    ,  2  // priority
    ,  &task1handle );

  xTaskCreate(
    Task2
    ,   "AnalogRead"
    ,  128 // This stack size can be checked & adjusted by reading Highwater
    ,  NULL
    ,  1  // priority
    ,  &task2handle );

  // Now the task scheduler, which takes over control of scheduling individual tasks, is automatically started.
}

void loop()
{
  // Empty. Things are done in Tasks.
}
