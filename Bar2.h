#include "HX711.h"
//Kalibrator
//selang kecil

const int PINOUT2 = 35;
const int PINSCK2 = 33;

HX711 scale2;
float pressure2, tekan2;

void Bar2S() {
  scale2.begin(PINOUT2, PINSCK2);
  scale2.set_gain(64);
}

void Bar2L() {
  if (scale2.is_ready()) {
    pressure2 = (scale2.read() + 7967) / 10;
    // tekan2 = 0.000238 * pressure2 + 900;
    // tekan2 = 0.000238 * pressure2 + 900 + 1.49 + 4.15 + 13.5;
    tekan2 = 0.000238 *pressure2 + 900 + 1.49 + 4.15 + 15.57;
    if (tekan2 < 0) {
      tekan2 = -tekan2;
    }
  }
}
