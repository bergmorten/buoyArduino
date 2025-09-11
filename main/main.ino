#define console Serial

static bool isInitilized = false;
const long taskInterval = 10000;  // 10s
static unsigned long lasTaskTime = 0;
// the setup function runs once when you press reset or power the board
void setup() {

  // This is main serial console / debug
  console.begin(230400);  // You may need to increase this for high navigation rates!

  while (!console)
    ;  //Wait for user to open terminal
  console.println("Starting project Buoy");
  // initialize other tasks
  setupLed();
  setupUblox();
  setupRockBlock();
  isInitilized = true;
}


// the loop function runs over and over again forever
void loop() {
  updateLed();
  if (millis() - lasTaskTime >= taskInterval) {
    checkNav();
    lasTaskTime = millis();
  }
  delay(500);  // Should do sleep instead for low power
}
