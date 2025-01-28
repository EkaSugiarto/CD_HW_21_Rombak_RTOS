String jsonString;

void addJson(String key, String value) {
  if (jsonString.length() > 1) jsonString += ",";
  jsonString += "\"" + key + "\":\"" + String(value) + "\"";
}

String getJson() {
  return "{" + jsonString + "}";
}

void Send_data() {
  WiFiClientSecure* client = new WiFiClientSecure;
  client->setInsecure();

  Serial.println("[BiruLangit] Starting POST ...");

  HTTPClient https;
  int httpCode;
  String api = "https://aelabp316.pythonanywhere.com/ESP_udara/post-data";

  addJson("created_at", get_precission_second(0));
  addJson("ws", String(WSV));
  addJson("debit_pompa", String(input));
  addJson("debit_setpoint", String(setpoint));

  if (https.begin(*client, api)) {
    https.addHeader("Content-Type", "application/json");

    Serial.println("[BiruLangit] " + getJson());

    httpCode = https.POST(getJson());

    if (httpCode >= 200 && httpCode <= 299) {
      Serial.println("[BiruLangit] POST sent! Code: " + String(httpCode) + "\n");
    } else {
      Serial.println("[BiruLangit] POST failed! Code: " + String(httpCode) + "\n");
      WiFi.disconnect();
    }
    https.end();
  }

  delete client;
  jsonString = "";
}