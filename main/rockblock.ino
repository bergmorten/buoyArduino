
#include <rockblock_9704.h>
#define rockBlockSerial Serial1  // Use Serial1 to connect to the GNSS module. Change this if required

static const int Serial1_TX = 16;  // grey wire to rx on iridium
static const int Serial1_RX = 17;  // blue wire to tx on iridium
static const int Iridium_EN = 22;  // orange
static const int Idium_BTD = 21;   // blue

static const long checkMessagesEvery = 1000;     // 1 second
static const long checkMessagesFor = 1000 * 30;  // 30 seconds;

char *mtBuffer = NULL;
int oldSignal;


bool setupRockBlock() {
  pinMode(Iridium_EN, OUTPUT);
  pinMode(Idium_BTD, INPUT);
  digitalWrite(Iridium_EN, LOW);  // Trun Iridium Off
  rockBlockSerial.begin(230400);
  return true;
}
static void _rockPowerOn() {
  while (rockBlockSerial.available() > 0) {
    rockBlockSerial.read();  // Read and discard each character
  }
  digitalWrite(Iridium_EN, HIGH);  // Turn Iridium Off

  while (digitalRead(Idium_BTD) == LOW) {
    updateLed();
    delay(100);
  }
  console.println("IRidium 9704 is booted");
}

void _rockPowerOff() {
  digitalWrite(Iridium_EN, LOW);  // Trun Iridium Off
}

void _rockPolMessages() {
  if (rbBegin("Serial1")) {
    console.println("Successfully started serial session with RB9704\r\n");

  } else {
    console.println("Failed to begin the serial connection with RB9704\r\n");
    return;
  }
  const unsigned long startTime = millis();
  unsigned long lastRockBlockTime = 0;

  while (millis() - startTime < checkMessagesFor) {

    if (millis() - lastRockBlockTime >= checkMessagesEvery) {
      lastRockBlockTime = millis();
      const size_t mtLength = rbReceiveMessage(&mtBuffer);
      if ((mtLength > 0) && (mtBuffer != NULL)) {
        console.print("Received MT at ");
        console.print(millis() - startTime);
        console.print("ms after boot, data: ");
        console.println(mtBuffer);
      }
      int newSignal = rbGetSignal();
      if (oldSignal != newSignal) {
        console.print("Current Signal: ");
        console.println(newSignal);
        oldSignal = newSignal;
      }
    }
    updateLed();
    delay(100);  // Short delay
  }
  //End serial connection
  if (rbEnd()) {
    console.println("Ended connection sucessfully\r\n");
  } else {
    console.println("Failed to end connection\r\n");
  }
}

bool rockCheckMessages() {

  if (!isInitilized) false;  // Global parameter
  // Clear UART buffer
  _rockPowerOn();
  _rockPolMessages();
  _rockPowerOff();


  return true;
}
