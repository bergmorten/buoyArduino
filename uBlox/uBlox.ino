// This Ardruine project turn on u-blox module and forward uart messages between its uart and pico usb-uart.

#include <SoftwareSerial.h>

SoftwareSerial uBloxSerial(XX, XX);  // RX, TX pins for software serial

void setup() {
  Serial.begin(230400);       // USB serial
  uBloxSerial.begin(230400);  // Software serial for u-blox
}

void loop() {
  if (uBloxSerial.available()) {
    char incomingByte = uBloxSerial.read();
    Serial.print(incomingByte);  // Forward to USB
  }
  if (Serial.available()) {
    char incomingByte = Serial.read();
    uBloxSerial.print(incomingByte);  // Forward from USB to u-blox
}
}