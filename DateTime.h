/*
  Kodingan untuk mendapatkan informasi tanggal dan waktu (date_time) untuk pengiriman & penyimpanan data
*/

// Library untuk menyimpan waktu pada RTC (Real-Time Clock) si ESP32
#include <ESP32Time.h>
// Objek dari ESP32Time dengan parameter -> offset 1 detik (ini bisa disesuaikan untuk ngepasin detik yg tersimpan di RTC ESP32 nya)
ESP32Time rtc(-2);

// Fungsi untuk mendapatkan date_time yg real
// Tulis parameter -> 0 untuk me-return date_time dengan format YYYY-MM-SS hh:mm:ss
// Tulis parameter -> 1 untuk me-return date_time dengan format YYYY-MM-SS
// Tulis parameter -> 2 untuk me-return date_time dengan format hh:mm:ss
String get_date_time(int choose) {
  String string_month, string_day, shour, sminute;

  rtc.getMonth() + 1 < 10 ? string_month = "0" + String(rtc.getMonth() + 1) : string_month = String(rtc.getMonth() + 1);
  rtc.getDay() < 10 ? string_day = "0" + String(rtc.getDay()) : string_day = String(rtc.getDay());

  switch (choose) {
    case 0:
      return String(rtc.getYear()) + "-" + string_month + "-" + string_day + " " + String(rtc.getTime());
      break;
    case 1:
      return String(rtc.getYear()) + "-" + string_month + "-" + string_day;
      break;
    case 2:
      return String(rtc.getTime());
      break;
  }
}


// Untuk mendapatkan date_time dengan minute dan second yang bisa disesuaikan.
// Kita bisa define mau menit dan detik berapa yg dituliskan nanti nya.
// Fungsi ini me-return date_time dengan format YYYY-MM-SS hh:mm:ss
String get_precission_minute_second(int minute, int seconds) {
  String shour, sminute, ssecond;

  rtc.getHour(true) < 10 ? shour = "0" + String(rtc.getHour(true)) : shour = String(rtc.getHour(true));
  minute < 10 ? sminute = "0" + String(minute) : sminute = String(minute);
  seconds < 10 ? ssecond = "0" + String(seconds) : ssecond = String(seconds);

  return get_date_time(1) + " " + shour + ":" + sminute + ":" + ssecond;
}


// Fungsi untuk mendapatkan date_time dengan detik yang bisa disesuaikan.
// Kita bisa tentukan mau detik berapa yang ditulis nanti nya.
// Fungsi ini me-return date_time dengan format YYYY-MM-SS hh:mm:ss
String get_precission_second(int seconds) {
  String shour, sminute, ssecond;

  rtc.getHour(true) < 10 ? shour = "0" + String(rtc.getHour(true)) : shour = String(rtc.getHour(true));
  rtc.getMinute() < 10 ? sminute = "0" + String(rtc.getMinute()) : sminute = String(rtc.getMinute());
  seconds < 10 ? ssecond = "0" + String(seconds) : ssecond = String(seconds);

  return get_date_time(1) + " " + shour + ":" + sminute + ":" + ssecond;
}


void Sync_RTC() {
  WiFiClientSecure* client = new WiFiClientSecure;
  client->setInsecure();

  HTTPClient https;
  int httpCode;
  String api = "https://serpongbrin.pythonanywhere.com/get-time";

  if (https.begin(*client, api)) {
    httpCode = https.GET();

    if (httpCode >= 200 && httpCode <= 299) {
      String payload = https.getString();

      int datetimeIndex = payload.indexOf("\"datetime\":");
      if (datetimeIndex != -1) {
        datetimeIndex = payload.indexOf("\"", datetimeIndex + 10) + 1;
        int datetimeEndIndex = payload.indexOf("\"", datetimeIndex);

        String datetime = payload.substring(datetimeIndex, datetimeEndIndex);

        if (datetime.length() >= 19) {
          int year = datetime.substring(0, 4).toInt();
          int month = datetime.substring(5, 7).toInt();
          int day = datetime.substring(8, 10).toInt();
          int hour = datetime.substring(11, 13).toInt();
          int minute = datetime.substring(14, 16).toInt();
          int second = datetime.substring(17, 19).toInt();

          rtc.setTime(second, minute, hour, day, month, year);
        } else {
          Serial.println("Error: Datetime string format is invalid!");
        }
      } else {
        Serial.println("Error: \"datetime\" key not found in JSON response.");
      }
      Serial.println("RTC synchronized: " + get_date_time(0));
    } else {
      Serial.println("Failed to get the date time!");
    }
    https.end();
  }

  delete client;
}

void Resync_RTC() {
  WiFiClientSecure* client = new WiFiClientSecure;
  client->setInsecure();

  HTTPClient https;
  int httpCode;
  String api = "https://serpongbrin.pythonanywhere.com/get-time";

  if (https.begin(*client, api)) {
    httpCode = https.GET();

    if (httpCode >= 200 && httpCode <= 299) {
      String payload = https.getString();

      int datetimeIndex = payload.indexOf("\"datetime\":");
      if (datetimeIndex != -1) {
        datetimeIndex = payload.indexOf("\"", datetimeIndex + 10) + 1;
        int datetimeEndIndex = payload.indexOf("\"", datetimeIndex);

        String datetime = payload.substring(datetimeIndex, datetimeEndIndex);

        if (datetime.length() >= 19) {
          int year = datetime.substring(0, 4).toInt();
          int month = datetime.substring(5, 7).toInt();
          int day = datetime.substring(8, 10).toInt();
          int hour = datetime.substring(11, 13).toInt();
          int minute = datetime.substring(14, 16).toInt();
          int second = datetime.substring(17, 19).toInt();

          if (abs(rtc.getSecond() - second) > 5) {
            rtc.setTime(second, minute, hour, day, month, year);
            Serial.println("RTC resynchronized: " + get_date_time(0));
          } else Serial.println("RTC already synchronized: " + get_date_time(0));
        } else {
          Serial.println("Error: Datetime string format is invalid!");
        }
      } else {
        Serial.println("Error: \"datetime\" key not found in JSON response.");
      }
      Serial.println("RTC synchronized: " + get_date_time(0));
    } else {
      Serial.println("Failed to get the date time!");
    }
    https.end();
  }

  delete client;
}