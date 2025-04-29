#include "VLUAVG.h"

VLUAVG::VLUAVG() {
  count = 0;
  index = 0;
  for (uint8_t i = 0; i < 10; i++) {
    temperatures[i] = 0.0;
    humidities[i] = 0.0;
  }
}

void VLUAVG::addData(float temp, float humi) {
  temperatures[index] = temp;
  humidities[index] = humi;
  index = (index + 1) % 10;
  if (count < 10) count++;
}

float VLUAVG::averageTemp() {
  if (count == 0) return 0.0;
  float sum = 0.0;
  for (uint8_t i = 0; i < count; i++) {
    sum += temperatures[i];
  }
  return sum / count;
}

float VLUAVG::averageHumi() {
  if (count == 0) return 0.0;
  float sum = 0.0;
  for (uint8_t i = 0; i < count; i++) {
    sum += humidities[i];
  }
  return sum / count;
}
