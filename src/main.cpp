#if CONFIG_FREERTOS_UNICORE
#define ARDUINO_RUNNING_CORE 0
#else
#define ARDUINO_RUNNING_CORE 1
#endif

#include <Arduino.h>
#include <Wire.h>  
#include <DHT.h>
#include <LiquidCrystal_I2C.h>
#include "VLUIoT.h"
#include "VLUAVG.h"

// DHT22 kết nối chân 23
#define DHTPIN 23
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);
VLUIoT ledRed(5);
VLUIoT ledOrange(4);
VLUAVG dataStorage;

// LCD 20x4, địa chỉ I2C là 0x27
LiquidCrystal_I2C lcd(0x27, 20, 4);

// Thời gian bật LED
uint32_t ledRedTime = 0;
uint32_t ledOrangeTime = 0;

void scanI2C() {
  byte error, address;
  Serial.println("Scanning I2C bus...");
  Wire.begin();
  for (address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    if (error == 0) {
      Serial.print("I2C device found at address 0x");
      if (address < 16) Serial.print("0");
      Serial.println(address, HEX);
    }
  }
}

void setup() {
  Serial.begin(115200);
  scanI2C();   // Quét kiểm tra LCD địa chỉ bao nhiêu
  delay(1000);

  dht.begin();
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("VLUIoT - Khoi dong");
  delay(1500);
  lcd.clear();
}

void loop() {
  float temp = dht.readTemperature();
  float humi = dht.readHumidity();

  if (!isnan(temp) && !isnan(humi)) {
    dataStorage.addData(temp, humi);

    float avgTemp = dataStorage.averageTemp();
    float avgHumi = dataStorage.averageHumi();

    Serial.print("Temp TB: ");
    Serial.print(avgTemp);
    Serial.print(" C | Humi TB: ");
    Serial.println(avgHumi);

    lcd.setCursor(0, 0);
    lcd.print("Nhiet do TB: ");
    lcd.print(avgTemp, 1);
    lcd.print((char)223);
    lcd.print("C   ");

    lcd.setCursor(0, 1);
    lcd.print("Do am TB   : ");
    lcd.print(avgHumi, 1);
    lcd.print("%   ");

    if (avgTemp > 28.0) {
      ledRed.blinkLed(1000);
      ledRedTime += 1000;
    }

    if (avgHumi > 70.0) {
      ledOrange.blinkLed(1000);
      ledOrangeTime += 1000;
    }

    lcd.setCursor(0, 2);
    lcd.print("LED Do   : ");
    lcd.print(ledRedTime / 1000);
    lcd.print("s     ");

    lcd.setCursor(0, 3);
    lcd.print("LED Cam  : ");
    lcd.print(ledOrangeTime / 1000);
    lcd.print("s     ");
  } else {
    Serial.println("Loi cam bien DHT22");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Doc DHT22 loi!");
  }

  delay(2000);
}
