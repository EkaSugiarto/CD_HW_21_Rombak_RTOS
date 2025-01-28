#include <PID_v1.h>

// #include "sinusiodal.h"
// #include "random-setpoint.h"

const int servoPin = 13;
const int pwmChannel = 0;
const int pwmFreq = 50;
const int pwmResolution = 16;

const int minAngle = 0;
const int maxAngle = 90;
const int servoMinDuty = 1500;
const int servoMaxDuty = 4915;

float persen, potValue;
float servoAngle;
float debit, selisih, selisih1;
float WS;

double setpoint, input, output;

double Kp = 0.5811, Ki = 12.6494, Kd = 0.00985;
// double Kp = 0.2, Ki = 8.6, Kd = 0.0002;

PID myPID(&input, &output, &setpoint, Kp, Ki, Kd, REVERSE);  //REVERSE, DIRECT

void KontrolL() {
  setpoint = flowrate;
  // setpoint = sineValue;
  // setpoint = random_set;

  selisih = fabs(pressure - pressure2);
  if (selisih < 0) {
    selisih = -selisih;
  }
  selisih1 = fabs(tekan - tekan2);
  if (selisih1 < 0) {
    selisih1 = -selisih1;
  }

  // debit = (-0.0325 * selisih1 * selisih1) + (1.667 * selisih1) + 0.6361; // Turun
  // debit = (-0.0408 * selisih1 * selisih1) + 1.8349 * selisih1 + 0.8699;  // Naik

  // debit = (-0.1126 * selisih1 * selisih1) + 2.7683 * selisih1 + 0.7205;

  debit = -0.0016 * (selisih1) * (selisih1) + 0.3558 * (selisih1) + 0.7594;  //terakhir

  input = debit;

  if (debit < 3) {
    setpoint = 3;
  } else if (debit > 17.5) {
    setpoint = 17.5;
  }

  myPID.Compute();
  output = constrain(output, 0, 90);
  int dutyCycle = map(output, 0, 90, servoMinDuty, servoMaxDuty);
  ledcWrite(pwmChannel, dutyCycle);

  Serial.println(String(tekan) + "," + String(tekan2) + "," + String(selisih1) + "," + String(setpoint) + "," + String(debit) + "," + String(WSV));
  Serial.println();
}