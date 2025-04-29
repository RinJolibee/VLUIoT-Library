#ifndef VLU_IOT_H
#define VLU_IOT_H

#include <Arduino.h>

class VLUIoT {
public:
  VLUIoT(uint8_t pin);
  void blinkLed(uint32_t durationMs);

private:
  uint8_t ledPin;
  static void ledBlinkTask(void *parameter);
};

#endif
