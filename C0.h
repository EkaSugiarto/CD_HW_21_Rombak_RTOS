bool WiFi_status;

void RTC_Sync(void *pvParameters) {
  while (1) {
    if (WiFi.status() == WL_CONNECTED && (rtc.getYear() < 2025)) {
      digitalWrite(2, LOW);
      Serial.println("Syncning RTC");
      Sync_RTC();
    } else digitalWrite(2, HIGH);
    vTaskDelay(500 / portTICK_PERIOD_MS);
    esp_task_wdt_reset();
  }
}


void RTC_Resync(void *pvParameters) {
  while (1) {
    if (WiFi.status() == WL_CONNECTED && rtc.getSecond() == 0 && rtc.getMinute() == 5) {
      Serial.println("Resyncning RTC");
      Resync_RTC();
    }
    vTaskDelay(500 / portTICK_PERIOD_MS);
    esp_task_wdt_reset();
  }
}

void WiFi_Connect(void *pvParameters) {
  while (1) {
    if (WiFi.status() != WL_CONNECTED) {
      digitalWrite(2, LOW);
      WiFi_status = false;
      Serial.println("Connecting to WiFi");
      char char_ssid[sizeof(ssid)];
      char char_pass[sizeof(pass)];
      ssid.toCharArray(char_ssid, sizeof(ssid));
      pass.toCharArray(char_pass, sizeof(pass));
      // WiFi.hostname(device);
      WiFi.mode(WIFI_STA);
      WiFi.begin(char_ssid, char_pass);
    } else WiFi_status = true;
    vTaskDelay(5000 / portTICK_PERIOD_MS);
    esp_task_wdt_reset();
  }
}


void Data_Send(void *pvParameters) {
  while (1) {
    if (rtc.getYear() >= 2024) {
      if (rtc.getSecond() == 5) {
        if (rtc.getMinute() % 2 == 0) {
          if (WiFi_status) Send_data();
        }
      }
    }
    vTaskDelay(100 / portTICK_PERIOD_MS);
    esp_task_wdt_reset();
  }
}