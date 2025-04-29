#include "VLUIoT.h"

typedef struct {
  uint8_t pin;
  uint32_t delayMs;
} LedTaskParam;

VLUIoT::VLUIoT(uint8_t pin) {
  ledPin = pin;
  pinMode(ledPin, OUTPUT);
}

void VLUIoT::blinkLed(uint32_t durationMs) {
  LedTaskParam *param = new LedTaskParam{ledPin, durationMs};

  xTaskCreatePinnedToCore(
    ledBlinkTask,
    "LedBlinkTask",
    1024,
    param,
    1,
    NULL,
    ARDUINO_RUNNING_CORE
  );
}

void VLUIoT::ledBlinkTask(void *parameter) {
  LedTaskParam *param = (LedTaskParam*) parameter;
  digitalWrite(param->pin, HIGH);
  vTaskDelay(param->delayMs / portTICK_PERIOD_MS);
  digitalWrite(param->pin, LOW);
  delete param;
  vTaskDelete(NULL);
}
