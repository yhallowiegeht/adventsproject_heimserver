#include "SenseBoxMCU.h"
#include <SPI.h>
#include <Wire.h>

Bee* b = new Bee();

void setup() {
  b->connectToWifi("Mehmet Scholl du Hurensohn","Wirhaben1neues");
  delay(2000);
  Serial.begin(300);
  Serial.print(b->getIpAddress());
}

void loop() {
}
