#include <Adafruit_ADS1X15.h>
#include <Wire.h>

Adafruit_ADS1115 ads;
int a0, a1, a2, a3;
float WSV, flowrate;

bool WSWD_state;

void WSS() {
  WSWD_state = ads.begin();
  ads.setGain(GAIN_TWOTHIRDS);
}

void WSL() {
  if (WSWD_state) {
    a1 = ads.readADC_SingleEnded(1);
    if (a1 < 0) a1 = 0;

    WSV = 0.0007 * a1;  //(a1 * 30.00 / 26500.00);//0.0007 * a2;
    if (WSV > 30) WSV = 30;
    flowrate = WSV * 4.71;
  }
}
