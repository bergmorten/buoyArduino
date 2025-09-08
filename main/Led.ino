
const long ledInterval = 500;  // 500ms
static unsigned long lastLedTime = 0;
static bool ledOn = false;
bool setupLed() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.println("LED is ready");
  return true;
}

void ledTask() {
    if (!isInitilized) return; // Global parameter
  if (millis() - lastLedTime >= ledInterval) {
    lastLedTime = millis();
    ledOn = !ledOn;
    
    if (ledOn) {
      digitalWrite(LED_BUILTIN, HIGH);
    } else {
      digitalWrite(LED_BUILTIN, LOW);
    }
  }
}