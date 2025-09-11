
const long ledInterval = 500;  // 500ms
static unsigned long lastLedTime = 0;
static bool statusLedOn = false;
bool setupLed() {
  pinMode(LED_BUILTIN, OUTPUT);
  console.println("LED is ready");
  return true;
}

void updateLed() {
  if (!isInitilized) return;  // Global parameter
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
