/*
  In this code I am creating and case where we have a DHT11 sensor (Digital Temperature and Humidity Sensor)
  to avoid hardware interfacing sensor fetcher task is going to dump dummy data to the queue
  the data will be dump as a structure which is the main goal of this exercise
*/
#include <Arduino_FreeRTOS.h>
#include <queue.h>

struct dht11 {
  float temperature = 0;
  float humidity = 0;
};

QueueHandle_t myQueueHandler;
TaskHandle_t dummyDHT11DataFetcherHandler;
TaskHandle_t queueDataExtractorHandlerL;

void dht_get(float &temp, float &humidity) {
  temp = temp + 0.50;
  humidity = humidity + 0.10;
}


void dummy_dht11_sensor_data_fetcher(void *pvParameter) {
  struct dht11 dummyDHT11;  //created a struct of dht11 type

  while (1) {
    dht_get(dummyDHT11.temperature, dummyDHT11.humidity);
    xQueueSend(myQueueHandler, &dummyDHT11, (TickType_t)0);
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}
void queue_data_extractor(void *pvParameter) {
  struct dht11 extractDHT11;
  while (1) {
    xQueueReceive(myQueueHandler, &extractDHT11, (TickType_t)0);
    vTaskDelay(100 / portTICK_PERIOD_MS);
    Serial.print("Temperature = ");
    Serial.println(extractDHT11.temperature);
    Serial.print("   ");
    Serial.print("Humidity = ");
    Serial.println(extractDHT11.humidity);
  }
}

void setup() {
  Serial.begin(9600);
  myQueueHandler = xQueueCreate(10, sizeof(dht11));
  xTaskCreate(dummy_dht11_sensor_data_fetcher, "dummy_dht11_sensor_data_fetcher", 128, NULL, 1, &dummyDHT11DataFetcherHandler);  // Creating task for generating dummy data
  xTaskCreate(queue_data_extractor, "queue_data_extractor", 128, NULL, 1, &queueDataExtractorHandlerL);                          // Creating task for receiving data from queue
}

void loop() {
  // put your main code here, to run repeatedly:
}
