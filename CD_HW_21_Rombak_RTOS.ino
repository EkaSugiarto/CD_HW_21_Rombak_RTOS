#include <esp_task_wdt.h>

String ssid = "Control_Onii-chan";
String pass = ">.<";

#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include "DateTime.h"

#include "WS.h"
#include "Bar1.h"
#include "Bar2.h"
#include "Kontrol_shift.h"

#include "Send_Data.h"

#include "Define_C0.h"
#include "Define_C1.h"

void setup() {
  Serial.begin(115200);

  esp_task_wdt_init(20, true);

  ledcSetup(pwmChannel, pwmFreq, pwmResolution);
  ledcAttachPin(servoPin, pwmChannel);

  WSS();
  Bar1S();
  Bar2S();

  C0S();
  C1S();

  myPID.SetMode(AUTOMATIC);
}

void loop() {
}
