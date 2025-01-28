#include "HX711.h"
//sensor 1
//selang besar

const int PINOUT = 34;
const int PINSCK = 25;

HX711 scale;
float pressure, voltase, tekan;

void Bar1S() {
  scale.begin(PINOUT, PINSCK);
  scale.set_gain(64);
}

void Bar1L() {
  if (scale.is_ready()) {
    pressure = scale.read();
    pressure = (0.8195 * pressure + 932703) / 10;
    // tekan = 0.000238 * pressure + 900;
    // tekan = 0.000238 *pressure + 900-24-0.8; //+ 1000;
    tekan = 0.000238 * pressure + 900;
    if(tekan<0){
      tekan = -tekan;
    }
  }
}
