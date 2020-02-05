
/*
   This code has two tasks
   AnalogRead which is increamenting a value of integer and sending it
   two second task named TaskSerial
   This is basic framwork where one can read sensor value and send it to
   second task for processing
*/
#include <Arduino_FreeRTOS.h>

// Include queue support
#include <queue.h>

QueueHandle_t integerQueue; //Declaring a global variable of type QueueHandle_t

int globel_integer = 0; // just a globel ordinary variable

void setup() {
  // Create a queue.
  integerQueue = xQueueCreate(10, // Queue length
                              sizeof(int) // Queue item size
                             );

  if (integerQueue != NULL)
  {
    // Create task that consumes the queue if it was created.
    xTaskCreate(TaskSerial, // Task function
                "Serial", // A name just for humans
                128,  // This stack size can be checked & adjusted by reading the Stack Highwater
                NULL,
                2, // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
                NULL);

    // Create task that publish data in the queue if it was created.
    xTaskCreate(TaskAnalogRead, // Task function
                "AnalogRead", // Task name
                128,  // Stack size
                NULL,
                1, // Priority
                NULL);
  }
}

void loop() {}//as usual loop will be empty and is there for making arduino to work


/*
   increaments the globel_integer and send it and send the readed value through the queue.
*/
void TaskAnalogRead(void *pvParameters)
{
  (void) pvParameters;

  for (;;)
  {
    // Read the input on analog pin 0:
    int sensorValue = globel_integer++;
    Serial.println("Message Sended by  TaskAnalogRead ");
    xQueueSend(integerQueue, &sensorValue, portMAX_DELAY);
    // One tick delay (15ms) in between reads for stability
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}

/**
   Serial task.
   Prints the received items from the queue to the serial monitor.
*/
void TaskSerial(void * pvParameters) {
  (void) pvParameters;

  // Init Arduino serial
  Serial.begin(9600);

  // Wait for serial port to connect.
  while (!Serial) {
    vTaskDelay(1);
  }

  int valueFromQueue = 0;
  
  while(1)
  {
    if (xQueueReceive(integerQueue, &valueFromQueue, portMAX_DELAY) == pdPASS)
    {
      Serial.print("Message received by TaskSerial is = ");
      Serial.println(valueFromQueue);
      vTaskDelay(500 / portTICK_PERIOD_MS);
    }
  }

}
