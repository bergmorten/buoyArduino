
#include <rockblock_9704.h>
#define rockBlockSerial Serial1 // Use Serial1 to connect to the GNSS module. Change this if required
const long rockBlockInterval = 1000;  // 1 second
static unsigned long lastRockBlockTime = 0;
bool ended = false;
char *mtBuffer = NULL;
int oldSignal;


bool setupRockBlock() {
  rockBlockSerial.begin(230400);
  delay(1000);
  if(rbBegin("Serial1"))
  {
      Serial.println("Successfully started serial session with RB9704\r\n");
      return false;
  
  }
  else
  {
      Serial.println("Failed to begin the serial connection with RB9704\r\n");
  }
  delay(1000);
  return true;
}


void rockBlockTask() {
  
  if (!isInitilized) return; // Global parameter

  if (millis() - lastRockBlockTime >= rockBlockInterval) {
    lastRockBlockTime = millis();
    if (!ended) {
      const size_t mtLength = rbReceiveMessage(&mtBuffer);
      if ((mtLength > 0) && (mtBuffer != NULL)) {
        Serial.print("Received MT: ");
        Serial.println(mtBuffer);
        //End serial connection
        if (rbEnd()) {
          Serial.println("Ended connection sucessfully\r\n");
          Serial1.end();
          ended = true;
        } else {
          Serial.println("Failed to end connection\r\n");
        }
      }
      int newSignal = rbGetSignal();
      if (oldSignal != newSignal) {
        Serial.print("Current Signal: ");
        Serial.println(newSignal);
        oldSignal = newSignal;
      }
    }
  }
}
