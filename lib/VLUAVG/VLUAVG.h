#ifndef VLUAVG_H
#define VLUAVG_H

#include <Arduino.h>

class VLUAVG {
public:
  VLUAVG();
  void addData(float temp, float humi);
  float averageTemp();
  float averageHumi();

private:
  float temperatures[10];
  float humidities[10];
  uint8_t count;
  uint8_t index;
};

#endif
