/*
* This code demostrate the use of binary semaphore
* For demo LCD/Serialport is used as a shared resource
*/

#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include <Arduino.h>

SemaphoreHandle_t mySemaphoreHandler = NULL;

void task1(void *pvParmeter)
{
  while (1)
  {
    xSemaphoreTake(mySemaphoreHandler, // for holding semaphore
                   portMAX_DELAY);     // for waiting till semaphore can't be taken
    for (int i = 0; i < 10; i++)
    {
      Serial.print("The Value of i = ");
      Serial.println(i);
    }
    Serial.println("*********** Task1 just giving up semaphore **********");

    xSemaphoreGive(mySemaphoreHandler);

    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void task2(void *pvParmeter)
{
  while (1)
  {
    xSemaphoreTake(mySemaphoreHandler, // for holding semaphore
                   portMAX_DELAY);     // for waiting till semaphore can't be taken
    for (int j = 0; j < 10; j++)
    {
      Serial.print("The Value of j = ");
      Serial.println(j);
    }
    Serial.println("########### Task2 just giving up semaphore ###########");

    xSemaphoreGive(mySemaphoreHandler);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void setup()
{
  Serial.begin(9600);
  mySemaphoreHandler = xSemaphoreCreateBinary();
  xSemaphoreGive(mySemaphoreHandler); /* Need to explore further why this is needed right after creation */

  xTaskCreate(task1, "ThisPrintsValueOfi", 128, NULL, 1, NULL);
  xTaskCreate(task2, "ThisPrintsValueOfij", 128, NULL, 1, NULL);
}

void loop()
{
}
