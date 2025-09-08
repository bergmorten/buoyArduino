// This Ardruine project turn on RockBlockmodule and forward uart messages between its uart and pico usb-uart.

#include <SoftwareSerial.h>

SoftwareSerial rockBlockSerial(XX, XX);  // RX, TX pins for software serial

void setup() {
  Serial.begin(230400);       // USB serial
  rockBlockSerial.begin(230400);  // Software serial for RockBlockmodule
}

void loop() {
  if (rockBlockSerial.available()) {
    char incomingByte = rockBlockSerial.read();
    Serial.print(incomingByte);  // Forward to USB
  }
  if (Serial.available()) {
    char incomingByte = Serial.read();
    rockBlockSerial.print(incomingByte);  // Forward from USB to RockBlockmodule
  }
}