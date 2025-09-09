

static bool isWorking = true;
const long sleepTime = 5000;  // 5s
static bool isInitilized = false;
// the setup function runs once when you press reset or power the board
void setup() {

  // This is main serial console / debug
  Serial.begin(230400);  // You may need to increase this for high navigation rates!

  while (!Serial)
    ;  //Wait for user to open terminal
  Serial.println("Starting project Buoy");
  // initialize other tasks
  setupLed();
  setupUblox();
  setupRockBlock();
  isInitilized = true;
}


// the loop function runs over and over again forever
void loop() {


  if (!isInitilized) {
    delay(1000);
    return;
  }
  ledTask();

  if (!isWorking) {
    // Should go to low power mode but wtf this was difficult with pico2
    delay(sleepTime);
  }
}
