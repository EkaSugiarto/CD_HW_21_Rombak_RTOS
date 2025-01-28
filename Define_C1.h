TaskHandle_t Sensor_Read_handler, Kontroling_handler;

#include "C1.h"

void C1S() {
  xTaskCreatePinnedToCore(
    Sensor_Read,
    "Sensor_Read",
    4096,
    NULL,
    1,
    &Sensor_Read_handler,
    1);

  xTaskCreatePinnedToCore(
    Kontroling,
    "Kontroling",
    4096,
    NULL,
    1,
    &Kontroling_handler,
    1);

  esp_task_wdt_add(Sensor_Read_handler);
  esp_task_wdt_add(Kontroling_handler);
}