
const long ledInterval = 500;  // 500ms
static unsigned long lastLedTime = 0;
static bool statusLedOn = false;
bool setupLed() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.println("LED is ready");
  return true;
}

void ledTask() {
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

bool strengthBar1(int level) {
  switch (level) {
    case 1:
      digitalWrite(LED_1_1, HIGH);
      digitalWrite(LED_1_2, LOW);
      digitalWrite(LED_1_3, LOW);
      digitalWrite(LED_1_4, LOW);
      digitalWrite(LED_1_5, LOW);
      break;
    case 2:
      digitalWrite(LED_1_1, HIGH);
      digitalWrite(LED_1_2, HIGH);
      digitalWrite(LED_1_3, LOW);
      digitalWrite(LED_1_4, LOW);
      digitalWrite(LED_1_5, LOW);
      break;
    case 3:
      digitalWrite(LED_1_1, HIGH);
      digitalWrite(LED_1_2, HIGH);
      digitalWrite(LED_1_3, HIGH);
      digitalWrite(LED_1_4, LOW);
      digitalWrite(LED_1_5, LOW);
      break;
    case 4:
      digitalWrite(LED_1_1, HIGH);
      digitalWrite(LED_1_2, HIGH);
      digitalWrite(LED_1_3, HIGH);
      digitalWrite(LED_1_4, HIGH);
      digitalWrite(LED_1_5, LOW);
      break;
    case 5:
      digitalWrite(LED_1_1, HIGH);
      digitalWrite(LED_1_2, HIGH);
      digitalWrite(LED_1_3, HIGH);
      digitalWrite(LED_1_4, HIGH);
      digitalWrite(LED_1_5, HIGH);
      break;
    default:
      digitalWrite(LED_1_1, LOW);
      digitalWrite(LED_1_2, LOW);
      digitalWrite(LED_1_3, LOW);
      digitalWrite(LED_1_4, LOW);
      digitalWrite(LED_1_5, LOW);
  }
}

bool strengthBar2(int level) {
  switch (level) {
    case 1:
      digitalWrite(LED_2_1, HIGH);
      digitalWrite(LED_2_2, LOW);
      digitalWrite(LED_2_3, LOW);
      digitalWrite(LED_2_4, LOW);
      digitalWrite(LED_2_5, LOW);
      break;
    case 2:
      digitalWrite(LED_2_1, HIGH);
      digitalWrite(LED_2_2, HIGH);
      digitalWrite(LED_2_3, LOW);
      digitalWrite(LED_2_4, LOW);
      digitalWrite(LED_2_5, LOW);
      break;
    case 3:
      digitalWrite(LED_2_1, HIGH);
      digitalWrite(LED_2_2, HIGH);
      digitalWrite(LED_2_3, HIGH);
      digitalWrite(LED_2_4, LOW);
      digitalWrite(LED_2_5, LOW);
      break;
    case 4:
      digitalWrite(LED_2_1, HIGH);
      digitalWrite(LED_2_2, HIGH);
      digitalWrite(LED_2_3, HIGH);
      digitalWrite(LED_2_4, HIGH);
      digitalWrite(LED_2_5, LOW);
      break;
    case 5:
      digitalWrite(LED_2_1, HIGH);
      digitalWrite(LED_2_2, HIGH);
      digitalWrite(LED_2_3, HIGH);
      digitalWrite(LED_2_4, HIGH);
      digitalWrite(LED_2_5, HIGH);
      break;
    default:
      digitalWrite(LED_2_1, LOW);
      digitalWrite(LED_2_2, LOW);
      digitalWrite(LED_2_3, LOW);
      digitalWrite(LED_2_4, LOW);
      digitalWrite(LED_2_5, LOW);
  }
}