#include <Arduino_FreeRTOS.h>

char mySharedResource[10];//this array is going to be a shared resource

void Task1(void *pvParameters)  // This is a task.
{
  (void) pvParameters;
    Serial.begin(9600);

  char TaskMsg1[] = "potatoes";
  /*
     Basically I'm intentionally going to write potatoes into
     shared resource character by character with some delay following is the
     code and as usual in embedded systems tasks are being repeated so every thing 
     is in an infinate while loop
  */  

  
  while (1)
  {
    int i = 0;
    for ( i = 0; i < 9; i++)
    {
      mySharedResource[i] = TaskMsg1[i];
      vTaskDelay(50/portTICK_PERIOD_MS );
    }
    // initialize digital pin 13 as an output.
    mySharedResource[i] = 0;
    Serial.print("T1 - > ");
    Serial.println(mySharedResource);
  }
}

void Task2(void *pvParameters)  // This is a task.
{
  (void) pvParameters;
  Serial.begin(9600);
  char TaskMsg2[] = "tomatoes";
 while (1)
  {
  int i = 0;
    for ( i = 0; i < 9; i++)
    {
      mySharedResource[i] = TaskMsg2[i];
      vTaskDelay(50/portTICK_PERIOD_MS );
    }
    // initialize digital pin 13 as an output.
    mySharedResource[i] = 0;
    Serial.print("T2 - > ");
    Serial.println(mySharedResource);
  }
}

TaskHandle_t task1handle;
TaskHandle_t task2handle;

// the setup function runs once when you press reset or power the board
void setup() {

  // Now set up two tasks to run independently.
  xTaskCreate(
    Task1
    ,  "task1"   // A name just for humans
    ,  128  // Stack size
    ,  NULL
    ,  2  // priority
    ,  &task1handle );//this is task Handler

  xTaskCreate(
    Task2
    ,   "task2"
    ,  128 // This stack size can be checked & adjusted by reading Highwater
    ,  NULL
    ,  1  // priority
    ,  &task2handle );//this is task Handler

  // Now the task scheduler, which takes over control of scheduling individual tasks, is automatically started.
}

void loop()
{
  // Empty. Things are done in Tasks.
}
