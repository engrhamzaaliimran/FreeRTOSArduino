#include<Arduino_FreeRTOS.h>

TaskHandle_t myTaskHandler;

void myTask(void *pvParameter)
{
  int priority = 0;
  while(1)
  {
    priority = uxTaskPriorityGet(myTaskHandler);
    Serial.print("My Priority is = ");
    Serial.print(priority);
    Serial.println();
  }
}

void setup() {
  Serial.begin(9600);
  xTaskCreate(myTask,"CheckingPriority",128,NULL,1,&myTaskHandler);

}

void loop() {
  // put your main code here, to run repeatedly:

}
