//https://haxiot.com/shop/arduino-lorawan-us900/

// In the below example you will need AppKey, DevAddr, Appskey & Nwkskey from the LoRaWAN Network Server provider.
// The Arduino library will by default set DevEUI to the embedded read-only value in the module unless another value is entered
#include <LoRaWAN.h>
#include <SoftwareSerial.h>

#define ON 1
#define OFF 0

//************** Device parameters for registration *****************
char DEVICE_ADDR[] = "00CF9C45";  //4 bytes required  this test device 

//Test's test shield deveui is :0004A30B001A414B

char APP_SESSION_KEY[] = "CA13DA3F3978686302F7D9EA5AC26AC8"; //16 bytes required
char APP_KEY[] = "F7AF2CB2D667DB442E7F921F8CAED6D0"; //16 bytes required
char APP_EUI[] =  "0000000000000000";  //8 bytes required
char NWK_SESSION_KEY[] = "ED157D1344D6A55462131A1CED2F80A5"; // 16 bytes required

char txData[] = "01020304050";    //sample data to be transmitted - must be hexadecimal values

LoRaWAN LoRaWAN(4, 5); // Software Serial RX, TX   ** Set to 10, 11 for Mega2560 boards, Set to 4,5 for Uno
void setup()
{
  delay(1000);                //startup delay - gives Lora module time to reset if cold start
  Serial.begin(9600);        //terminal serial port, 9600 = Default, 57600 = Haxiot shield

  //LoRaWAN.LoRaResetModule();                          //restore module to factory default settings and reset device
  LoRaWAN.LoRaDeviceEUI();                            //retrieves EUI from module and auto sets
  LoRaWAN.LoRaDevAddr(DEVICE_ADDR);                   //sets device address
  LoRaWAN.LoRaApplicationSessionKey(APP_SESSION_KEY); //sets application session key
  LoRaWAN.LoRaApplicationKey(APP_KEY);                //sets application key
    LoRaWAN.LoRaNetworkSessionKey(NWK_SESSION_KEY);     //sets network session key
  LoRaWAN.LoRaAdaptiveDataRate(ON);      //set to ON to enable, OFF to disable
  LoRaWAN.LoRaTXPower(20);                //dBM 10(Min), 12, 14, 16, 18, 20(Max)
  LoRaWAN.LoRaChannelPlan(8, 15);         //(start channel, end channel) - channel range 0 to 63
  LoRaWAN.LoRaSaveConfig();                           //save configuration settings to module eeprom

  //************* Connect to LoRaWAN Network Server****************//
  // Comment out
  LoRaWAN.LoRaJoinABP ();       //Connect with Access By Personalization (ABP) networks

  LoRaWAN.LoRaShowConfig();             //display current module configuration for debugging only

}

void loop() {

  //*************** Display received data from LoRaWAN
  while (LoRaWAN.loraSerial.available())
  {
    Serial.write(LoRaWAN.loraSerial.read());
  }

  {
    //*************** Display then transmit data to LoRaWAN
    Serial.print("Sending: "); Serial.println(txData);
    LoRaWAN.LoRaTransmit(0, 30, txData);   //type 0 = Confirmed, 1 = Unconfirmed / port number 1 to 223 / data payload
    delay(60000);
  }
}
