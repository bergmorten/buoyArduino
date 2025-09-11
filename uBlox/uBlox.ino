// This Ardruine project turn on u-blox module and forward uart messages between its uart and pico usb-uart.

#define uBloxSerial Serial2
#define console Serial

const int Serial1_TX = 16;  // grey wire to rx on iridium
const int Serial1_RX = 17;  // blue wire to tx on iridium

const int Iridium_EN = 22;  // orange
const int Idium_BTN = 21;   // blue

const int Serial2_TX = 4;  // to rx GNSS NB start on serial 1 (serial 0 is USB)
const int Serial2_RX = 5;  // to tx GNSS NB start on serial 1 (serial 0 is USB)

const int ubloxPowerOn = 18;

static bool statusLedOn = false;
const long ledInterval = 500;  // 500ms
static unsigned long lastLedTime = 0;

void setup() {

  // Enable status led
  pinMode(LED_BUILTIN, OUTPUT);

  // Iridium
  pinMode(Iridium_EN, OUTPUT);
  pinMode(Idium_BTN, INPUT);
  digitalWrite(Iridium_EN, LOW);  // Trun Irdium Off

  // Turn on power
  pinMode(ubloxPowerOn, OUTPUT);
  digitalWrite(ubloxPowerOn, HIGH);  // Trun GNSS ON
  delay(1000);                       // Wait to power to settle

  uBloxSerial.setRX(Serial2_RX);  // Assingn pin
  uBloxSerial.setTX(Serial2_TX);  // Assign pin
  uBloxSerial.setFIFOSize(128);   // Increase FIFO
  uBloxSerial.begin(38400);       // Serial for uBlox
  console.begin();           // USB serial
}

void loop() {

  if (uBloxSerial.available()) {
    char incomingByte = uBloxSerial.read();
    console.print(incomingByte);  // Forward from uBlox to USB
  }

  if (console.available()) {
    char incomingByte = console.read();
    uBloxSerial.print(incomingByte);  // Forward from USB to uBlox
  }

  if (millis() - lastLedTime >= ledInterval) {
    lastLedTime = millis();
    statusLedOn = !statusLedOn;

    if (statusLedOn) {
      digitalWrite(LED_BUILTIN, HIGH);
    } else {
      digitalWrite(LED_BUILTIN, LOW);
    }
  }
}