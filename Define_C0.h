TaskHandle_t WiFi_Connect_handler, RTC_Sync_handler, RTC_Resync_handler, Data_Send_handler;

#include "C0.h"

void C0S() {
  xTaskCreatePinnedToCore(
    WiFi_Connect,
    "WiFi_Connect",
    4096,
    NULL,
    5,
    NULL,
    0);

  xTaskCreatePinnedToCore(
    RTC_Sync,
    "RTC_Sync",
    8192,
    NULL,
    1,
    NULL,
    0);

  xTaskCreatePinnedToCore(
    RTC_Resync,
    "RTC_Resync",
    8192,
    NULL,
    1,
    NULL,
    0);

  xTaskCreatePinnedToCore(
    Data_Send,
    "Data_Send",
    8192,
    NULL,
    1,
    NULL,
    0);

  esp_task_wdt_add(WiFi_Connect_handler);
  esp_task_wdt_add(RTC_Sync_handler);
  esp_task_wdt_add(RTC_Resync_handler);
  esp_task_wdt_add(Data_Send_handler);
}