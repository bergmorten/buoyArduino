
#define MAX_PAYLOAD_SIZE 384  // Override MAX_PAYLOAD_SIZE for getModuleInfo which can return up to 348 bytes
#include <SparkFun_u-blox_GNSS_v3.h>
#define uBloxSerial Serial2       // Use Serial2 to connect to the GNSS module. Change this if required
static const int Serial2_TX = 4;  // to rx GNSS NB start on serial 1 (serial 0 is USB)
static const int Serial2_RX = 5;  // to tx GNSS NB start on serial 1 (serial 0 is USB)
static const int ubloxPowerOn = 18;

SFE_UBLOX_GNSS_SERIAL myGNSS;
static const long updateEvery = 100;       // 1 second
static const long checkNavFor = 1000 * 30;  // 30 seconds;

bool setupUblox() {
  console.println("Starting u-blox");

  // Turn on power
  pinMode(ubloxPowerOn, OUTPUT);
  digitalWrite(ubloxPowerOn, HIGH);  // Trun GNSS On for configuration
  uBloxSerial.setRX(Serial2_RX);     // Assingn pin
  uBloxSerial.setTX(Serial2_TX);     // Assign pin
  uBloxSerial.setFIFOSize(128);      // Increase FIFO
  uBloxSerial.begin(38400);          // u-blox modules default to 38400 baud. Change this if required
  delay(1000);

  /*
 if (uBloxSerial.available() > 0) {
    char msg = uBloxSerial.read();  // Read and discard each character
    console.print("got data: ");
    console.println(msg);
  }
  */
  if (myGNSS.begin(uBloxSerial) == false)  //Connect to the u-blox module using UART port
  {
    console.println(F("u-blox GNSS not detected at default UART address. Please check wiring...."));
    return false;
  }

  myGNSS.setUART1Output(COM_TYPE_UBX);  //Set the UART  port to output UBX only (turn off NMEA noise)
  myGNSS.setNavigationFrequency(5);     // Produce five solutions per second
  myGNSS.setAutoPVT(true);              // Tell the GNSS to output each solution periodically

  //myGNSS.saveConfigSelective(VAL_CFG_SUBSEC_IOPORT);  //Save (only) the communications port settings to flash and BBR
  myGNSS.saveConfiguration();
  console.println("GNSS uBlox is ready");
  digitalWrite(ubloxPowerOn, LOW);  // Trun GNSS Off
  return true;
}

void _ubloxPowerOn() {
  // UART Buffer
  while (uBloxSerial.available() > 0) {
    uBloxSerial.read();  // Read and discard each character
  }
  digitalWrite(ubloxPowerOn, HIGH);  // Trun GNSS ON
}

void _ubloxPowerOff() {
  digitalWrite(ubloxPowerOn, LOW);  // Trun GNSS OFF
}

void _ubloxPoolNav() {
  if (myGNSS.begin(uBloxSerial) == false)  //Connect to the u-blox module using UART port
  {
    console.println(F("u-blox GNSS not detected at default UART address. Please check wiring...."));
    return;
  }

  const unsigned long startTime = millis();
  unsigned long lastNavTime = 0;

  while (millis() - startTime < checkNavFor) {

    //The module only responds when a new position is available
    if (millis() - lastNavTime > updateEvery) {
      lastNavTime = millis();  //Update the timer

      long latitude = myGNSS.getLatitude();
      console.print(F("Lat: "));
      console.print(latitude);

      long longitude = myGNSS.getLongitude();
      console.print(F(" Long: "));
      console.print(longitude);
      console.print(F(" (degrees * 10^-7)"));

      long altitude = myGNSS.getAltitude();
      console.print(F(" Alt: "));
      console.print(altitude);
      console.print(F(" (mm)"));

      byte SIV = myGNSS.getSIV();
      console.print(F(" SIV: "));
      console.print(SIV);

      console.println();
    }
    updateLed();
    delay(10);  // Short delay
  }
}

bool checkNav() {

  if (!isInitilized) return false;  // Global parameter
  console.println("uBlox task starting");
  _ubloxPowerOn();
  _ubloxPoolNav();
  _ubloxPowerOff();
  console.println("uBlox task finnish");
  return true;
}