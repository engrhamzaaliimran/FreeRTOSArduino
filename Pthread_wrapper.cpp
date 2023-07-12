#include "Arduino_FreeRTOS.h"
#include "task.h"

typedef TaskHandle_t pthread_t;
typedef void* pthread_attr_t;
typedef void* pthread_mutex_t;

int pthread_create(pthread_t* thread, const pthread_attr_t* attr, void* (*start_routine)(void*), void* arg) {
    return xTaskCreate(start_routine, "Thread", configMINIMAL_STACK_SIZE, arg, tskIDLE_PRIORITY, thread) == pdPASS ? 0 : -1;
}

int pthread_join(pthread_t thread, void** retval) {
    vTaskDelete(thread);
    return 0;
}

int pthread_mutex_init(pthread_mutex_t* mutex, const void* attr) {
    *mutex = xSemaphoreCreateMutex();
    return *mutex != NULL ? 0 : -1;
}

int pthread_mutex_lock(pthread_mutex_t* mutex) {
    return xSemaphoreTake(*mutex, portMAX_DELAY) == pdTRUE ? 0 : -1;
}

int pthread_mutex_unlock(pthread_mutex_t* mutex) {
    return xSemaphoreGive(*mutex) == pdTRUE ? 0 : -1;
}
