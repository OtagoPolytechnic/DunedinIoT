//http://www.instructables.com/id/Arduino-Sleep-and-Wakeup-Test-With-DS3231-RTC/
//https://github.com/rocketscream/Low-Power/

#include <Wire.h>
#include <RTClibExtended.h> 
#include <LowPower.h> //modified for Mega 2560

#define wakePin 2    //use interrupt 0 (pin 2) and run function wakeUp when pin 2 gets LOW
#define ledPin 13    //use arduino on-board led for indicating sleep or wakeup status

RTC_DS3231 RTC;      //we are using the DS3231 RTC

byte AlarmFlag = 0;

//-------------------------------------------------

void wakeUp()        // here the interrupt is handled after wakeup
{
  
}

//------------------------------------------------------------

void setup() 
{
  //Set pin D2 as INPUT for accepting the interrupt signal from DS3231
  pinMode(wakePin, INPUT);

  //switch-on the on-board led for 1 second for indicating that the sketch is ok and running
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);
  delay(1000);

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

  //SETTING ALARMS
  //There are different modes for every minute, every second, a given time, a second of every minute, a minute of every hour... etc
  //You need to read the source code to understand them
  //RTC.setAlarm(ALM1_MATCH_SECONDS, 15, 0, 0, 0);   //15th second of every minute
  //RTC.alarmInterrupt(1, true);
  RTC.setAlarm(ALM2_EVERY_MINUTE, 0, 0 ,0); // every minute, other given values are ignored (can't say "every six minutes")
  RTC.alarmInterrupt(2, true);    //sets the interrrupt pin working with this alarm
}

//------------------------------------------------------------

void loop() 
{
  //On first loop we enter the sleep mode
  if (AlarmFlag == 0) 
  {
    attachInterrupt(0, wakeUp, LOW);                       //use interrupt 0 (pin 2) and run function wakeUp when pin 2 gets LOW 
    digitalWrite(ledPin, LOW);                             //switch-off the led for indicating that we enter the sleep mode
    LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);   //arduino enters sleep mode here
    detachInterrupt(0);                                    //execution resumes from here after wake-up

    //When exiting the sleep mode we clear the alarm
    //RTC.armAlarm(1, false);     //un commenting this line stops sleep happening next time
    RTC.clearAlarm(2);
    //RTC.alarmInterrupt(1, false); //un commenting this line stops sleep happening next time
    AlarmFlag++;
  }

  //code to run after waking
  digitalWrite(ledPin, HIGH);
  delay(3000);
  //now set the alarm flag zero so we go back to sleep
  AlarmFlag = 0;
}

