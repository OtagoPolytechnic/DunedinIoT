
//https://github.com/FabioCuomo/FabioCuomo-DS3231

#include <RTClibExtended.h>
#include <Wire.h>

RTC_DS3231 RTC;      //we are using the DS3231 RTC
DateTime currentTime;
void setup() 
{
  //Start serial for output
  Serial.begin(9600);
  
  //Initialize communication with the clock
  Wire.begin();
  RTC.begin();
  RTC.adjust(DateTime(__DATE__, __TIME__));   //set RTC date and time to COMPILE time
  
  //clear any pending alarms
  RTC.armAlarm(1, false);
  RTC.clearAlarm(1);
  RTC.alarmInterrupt(1, false);
  RTC.armAlarm(2, false);
  RTC.clearAlarm(2);
  RTC.alarmInterrupt(2, false);

  //Set SQW pin to OFF (in my case it was set by default to 1Hz)
  //The output of the DS3231 INT pin is connected to this pin
  //It must be connected to arduino D2 pin for wake-up
  RTC.writeSqwPinMode(DS3231_OFF);
}

void loop() 
{
  //get the current time
  currentTime = RTC.now();

  //build the output
  String output = (String)currentTime.year();
  output += "-";
  output += (String)currentTime.month();
  output += "-";
  output += (String)currentTime.day();
  output += "_";
  output += (String)currentTime.hour();
  output += "-";
  output += (String)currentTime.minute();
  output += "-";
  output += (String)currentTime.second();

  //output to serial to test
  Serial.println(output);
  delay(1000);
}
