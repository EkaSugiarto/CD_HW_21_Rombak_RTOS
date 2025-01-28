void Sensor_Read(void *pvParameters) {
  while (1) {
    WSL();
    Bar1L();
    Bar2L();
    vTaskDelay(100 / portTICK_PERIOD_MS);
    esp_task_wdt_reset();
  }
}

void Kontroling(void *pvParameters) {
  while (1) {
    KontrolL();
    vTaskDelay(100 / portTICK_PERIOD_MS);
    esp_task_wdt_reset();
  }
}