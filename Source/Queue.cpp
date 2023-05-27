#include <Arduino_FreeRTOS.h>
#include <queue.h>  // this is to be included if we want to create queues


QueueHandle_t intergerQueueHandler = NULL;
TaskHandle_t dummyDataTaskHandler = NULL;
TaskHandle_t dataConsumingTaskHandler = NULL;


int dummySensorValue = 0;

void dummy_sensor_data_task(void *pvParameter) {
  while (1) {
    xQueueSend(intergerQueueHandler  //handler to the queue where the data will be dummped
               ,
               &dummySensorValue  //The pointer to the variable having the data to be writen to the Queue
               ,
               (TickType_t)0  // To not block the task if queue is not available to write the data in it
    );
    dummySensorValue++;
    if (dummySensorValue > 10)
      dummySensorValue = 0;
  }
}
void data_consuming_task(void *pvParameter) {
  int receiveData = 0;
  while (1) {
    xQueueReceive(intergerQueueHandler,  //handle of the queue from which data is to be extracted
                  &receiveData,          // The pointer to the variable/buffer to put data from queue
                  (TickType_t)0          // To not block the task if queue is not available to write the data in it
    );
    Serial.print("Sensor data extracted from queue = ");
    Serial.println(receiveData);
    vTaskDelay(400 / portTICK_PERIOD_MS);
  }
}


void setup() {
  Serial.begin(9600);

  intergerQueueHandler = xQueueCreate(
    10  //ten number of units in queue
    ,
    sizeof(int)  // Queue item size
  );

  if (intergerQueueHandler == NULL) {
    Serial.print("Queue can't be created. The program is entering hault state.");
    while (1)
      ;  //Stay here for ever
  }
  xTaskCreate(dummy_sensor_data_task, "thisTaskProduceDummySensorData", 128, NULL, 1, &dummyDataTaskHandler);  // Creating task for generating dummy data
  xTaskCreate(data_consuming_task, "thisTaskReceivesDataFromQueue", 128, NULL, 1, &dataConsumingTaskHandler);  // Creating task for receiving data from queue
}

void loop() {
  // No need of any code here since scheduler already have the control of the program and we wil never reach this location.
}
