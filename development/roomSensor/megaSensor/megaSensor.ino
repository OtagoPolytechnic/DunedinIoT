/*
 * A smart room sensor data logger
 * 
 * Measures: Lux level, sound level, temperature, and logs the data to an SD card, sleeping between readings.
 * Authors: Campbell McDowall and Brendan Kelly
 * Date: March-May 2017
 * Requires: Ardunio Mega
 * 
 */

/*-------------------------------------------------------------
 * Code sources and examples
 *-------------------------------------------------------------
 * Lux sensor: https://learn.adafruit.com/tsl2561/use
 * DHT22 temperature/humidity sensor: https://learn.adafruit.com/dht/connecting-to-a-dhtxx-sensor
 * Sound sensor: https://learn.adafruit.com/adafruit-microphone-amplifier-breakout/measuring-sound-levels
 * RTC sleep and wake with Low-Power library: http://www.instructables.com/id/Arduino-Sleep-and-Wakeup-Test-With-DS3231-RTC/
 *                                            https://github.com/FabioCuomo/FabioCuomo-DS3231
 *                                            https://github.com/rocketscream/Low-Power/
 *             Fixing Low-Power for Mega2560: https://github.com/rocketscream/Low-Power/issues/30                                                                  
 * RTC date/time to text: https://github.com/FabioCuomo/FabioCuomo-DS3231
 * PIR Motion sensor: https://learn.adafruit.com/pir-passive-infrared-proximity-motion-sensor/connecting-to-a-pir
 *                    https://learn.adafruit.com/pir-passive-infrared-proximity-motion-sensor/using-a-pir
 * 
 * CSV format is "Date/time, Sound level, temperature, humidity, Lux level, motion detected (HIGH/LOW)"
 *-------------------------------------------------------------
 *End code sources and examples
 *-------------------------------------------------------------
 */

#include <Wire.h>

//rtc
#include <RTClibExtended.h>
#include <LowPower.h>
//lux
#include <Adafruit_Sensor.h>
#include <Adafruit_TSL2561_U.h>
//sd
#include <SPI.h>
#include <SD.h>

#define wakePin 2    //use interrupt 0 (pin 2) and run function wakeUp when pin 2 gets LOW
#define ledPin 8     //pin our notification LED is attached to

RTC_DS3231 rtc;      //we are using the DS3231 RTC

byte AlarmFlag = 0;

//--------------------------------------
// PIR motion sensor
//--------------------------------------

int PIRPIN = 10;      // choose the input pin for PIR sensor

//--------------------------------------
// End PIR motion sensor
//--------------------------------------


//--------------------------------------
// Lux
//--------------------------------------

Adafruit_TSL2561_Unified tsl = Adafruit_TSL2561_Unified(TSL2561_ADDR_FLOAT, 12345);

//--------------------------------------
//End Lux
//--------------------------------------


//--------------------------------------
//SD card
//--------------------------------------
// set up variables using the SD utility library functions:
Sd2Card card;
SdVolume volume;
SdFile root;

File myFile;
String fileName = "test6.csv";

// change this to match your SD shield or module;
const int chipSelect = 53;    //we are using digital pin 10
//--------------------------------------
// End SD card
//--------------------------------------


//--------------------------------------
//Sound
//--------------------------------------
const int sampleWindow = 50; // Sample window width in mS (50 mS = 20Hz)
unsigned int sample;
//--------------------------------------
//End sound
//--------------------------------------

//--------------------------------------
//Temperature and humidity
//--------------------------------------
//!!! IMPORTANT !!! :
//The Adafruit DHT22 library must be installed.
//The Adafruit Unified Sensor lbrary must be installed.
//There should be a 10KOhm resistor between the data pin and 5V DCC.

#include <DHT.h>

//set the data pin
#define DHTPIN 3

//set the DHT type
#define DHTTYPE DHT22

//atmospheric variables
float humidityPercent;
float tempC;

//the time
DateTime currentTime;

//instantiate dht
DHT dht(DHTPIN, DHTTYPE);
//--------------------------------------
//End temperature and humidity
//--------------------------------------

//holds the data to be written to the SD card
String dataString = "";


//--------------------------------------
//Set up
//--------------------------------------
void setup()
{

  //Set pin D2 as INPUT for accepting the interrupt signal from DS3231
  pinMode(wakePin, INPUT);

  //switch-on the on-board led for 1 second for indicating that the sketch is ok and running
  pinMode(ledPin, OUTPUT);

  Serial.begin(9600);

  //Initialize communication with the clock
  Wire.begin();
  rtc.begin();
  DateTime now = rtc.now();
  DateTime compiled = DateTime(__DATE__, __TIME__);
  //if the RTC time is older than the compile time, reset clock
  if (now.unixtime() < compiled.unixtime())
  {
    Serial.println("RTC is older than compile time! Updating");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(__DATE__, __TIME__));
  }

  //clear any pending alarms
  rtc.armAlarm(1, false);
  rtc.clearAlarm(1);
  rtc.alarmInterrupt(1, false);
  rtc.armAlarm(2, false);
  rtc.clearAlarm(2);
  rtc.alarmInterrupt(2, false);

  //Set SQW pin to OFF (in my case it was set by default to 1Hz)
  //The output of the DS3231 INT pin is connected to this pin
  //It must be connected to Arduino D2 pin for wake-up
  rtc.writeSqwPinMode(DS3231_OFF);

  //SETTING ALARMS
  //There are different modes for every minute, every second, a given time, a second of every minute, a minute of every hour... etc
  //From the Low-Power library
  /*
    ALM1_EVERY_SECOND = 0x0F,
    ALM1_MATCH_SECONDS = 0x0E,
    ALM1_MATCH_MINUTES = 0x0C,     //match minutes *and* seconds
    ALM1_MATCH_HOURS = 0x08,       //match hours *and* minutes, seconds
    ALM1_MATCH_DATE = 0x00,        //match date *and* hours, minutes, seconds
    ALM1_MATCH_DAY = 0x10,         //match day *and* hours, minutes, seconds

    ALM2_EVERY_MINUTE = 0x8E,
    ALM2_MATCH_MINUTES = 0x8C,     //match minutes
    ALM2_MATCH_HOURS = 0x88,       //match hours *and* minutes
    ALM2_MATCH_DATE = 0x80,        //match date *and* hours, minutes
    ALM2_MATCH_DAY = 0x90,         //match day *and* hours, minutes
    */
  //rtc.setAlarm(ALM1_MATCH_SECONDS, 15, 0, 0, 0);   //15th second of every minute
  //rtc.alarmInterrupt(1, true);
  rtc.setAlarm(ALM2_EVERY_MINUTE, 0, 0 , 0); // every minute, other given values are ignored (can't say "every six minutes")
  rtc.alarmInterrupt(2, true);    //sets the interrrupt pin working with this alarm

  //start temp/humidity sensor
  dht.begin();

  //start the lux sensor
  Serial.println("Light Sensor Test"); Serial.println("");
  if (!tsl.begin())
  {
    /* There was a problem detecting the TSL2561 ... check your connections */
    Serial.print("Ooops, no TSL2561 detected ... Check your wiring or I2C ADDR!");
    while (1);
  }

  /* Setup the sensor gain and integration time */
  configureSensor();



  //--------------------------------------
  //SD card test
  //--------------------------------------
  while (!Serial)
  {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.print("Initializing SD card...");
  // On the Ethernet Shield, CS is pin 4. It's set as an output by default.
  // Note that even if it's not used as the CS pin, the hardware SS pin
  // (10 on most Arduino boards, 53 on the Mega) must be left as an output
  // or the SD library functions will not work.
  pinMode(53, OUTPUT);

  if (!SD.begin(53))
  {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");

  //--------------------------------------
  //End SD card test
  //--------------------------------------

  Serial.end();
}
//--------------------------------------
//End set up
//--------------------------------------


//--------------------------------------
//Main Loop
//--------------------------------------
void loop()
{
  Serial.begin(9600);
  //On first loop we enter the sleep mode
  if (AlarmFlag == 0)
  {
    attachInterrupt(0, wakeUp, LOW);                       //use interrupt 0 (pin 2) and run function wakeUp when pin 2 gets LOW
    digitalWrite(ledPin, LOW);                             //switch-off the led for indicating that we enter the sleep mode
    LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);   //arduino enters sleep mode here
    detachInterrupt(0);                                    //execution resumes from here after wake-up

    //When exiting the sleep mode we clear the alarm
    //rtc.armAlarm(1, false);     //un commenting this line stops sleep happening next time
    rtc.clearAlarm(2);
    //rtc.alarmInterrupt(1, false); //un commenting this line stops sleep happening next time
    //set alarm flag something other than zero so it will be detected
    AlarmFlag++;
  }

  //code to run after waking
  digitalWrite(ledPin, HIGH);
  delay(2000);

  Serial.print("Opening file");
  myFile = SD.open(fileName, FILE_WRITE);   //open sd card

  if (myFile) //if the file opened correctly
  {
    Serial.print("Writing to ");
    Serial.println(fileName);

    
   Serial.println("Reading sensors...");
    readTempHumiditySensor(); //reads the sensor
    if (isnan(humidityPercent) || isnan(tempC))    // Check if any reads failed and exit early (to try again)
    {
      Serial.println("Failed to read from DHT sensor!");
      return;
    }
    String DateTimeString = dateTime();                      //date and time of reading
    String soundLevel = (String)measureSoundLevel();          //currently only in volts TESTING
    String temperature = (String)tempC;                      //temp
    String humidity = (String)humidityPercent;               //humidity
    String lux = (String)measureLux();                         //lux
    String motion = (String)detectMotion();
    

    //build a string of the sensor outputs
    dataString = DateTimeString;
    dataString += ",";
    dataString += soundLevel;
    dataString += ",";
    dataString += temperature;
    dataString += ",";
    dataString +=  humidity;
    dataString += ",";
    dataString += lux;
    dataString += ",";
    dataString += motion;

    //output data to serial
    Serial.println("");
    Serial.println("combined datastring before write");
    Serial.println(dataString);
    //write data to csv file
    myFile.println(dataString); 
    //myFile.println(soundLevel);

    myFile.close();  // close the file:
    Serial.println("done");
    Serial.println("--------------------------------------");
  }
  else
  {
    // if the file didn't open, print an error:
    Serial.print("error opening ");
    Serial.print(fileName);
  }

  AlarmFlag = 0;  //now set the alarm flag zero so we go back to sleep
  Serial.end(); //turning off serial now should save power and avoid some sleeping issues
}
//--------------------------------------
//End main Loop
//--------------------------------------


//--------------------------------------
//Handle interrupt after wake up
//--------------------------------------
void wakeUp()
{
  //you don't need to do anything here
}
//--------------------------------------
//End handle interrupt after wake up
//--------------------------------------


//--------------------------------------
//Measure sound level
//--------------------------------------
double measureSoundLevel()
{
  unsigned long startMillis = millis(); // Start of sample window
  unsigned int peakToPeak = 0;   // peak-to-peak level

  unsigned int signalMax = 0;
  unsigned int signalMin = 1024;

  // collect data for 50 mS
  while (millis() - startMillis < sampleWindow)
  {
    sample = analogRead(0);
    if (sample < 1024)  // toss out spurious readings
    {
      if (sample > signalMax)
      {
        signalMax = sample;  // save just the max levels
      }
      else if (sample < signalMin)
      {
        signalMin = sample;  // save just the min levels
      }
    }
  }
  peakToPeak = signalMax - signalMin;  // max - min = peak-peak amplitude
  double volts = (peakToPeak * 5.0) / 1024;  // convert to volts

  return (volts); //testing currently will return volts as it is just taken from adafruit website
}
//--------------------------------------
//End measure sound level
//--------------------------------------


//--------------------------------------
//Measure temperature and humidity
//--------------------------------------
void readTempHumiditySensor()
{
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  humidityPercent = dht.readHumidity();
  // Read temperature as Celsius (the default)
  tempC = dht.readTemperature();
  // Compute heat index in Celsius (isFahreheit = false)
  //feelsLike = dht.computeHeatIndex(tempC, humidityPercent, false); // not using this
}
//--------------------------------------
//End measure temperature and humidity
//--------------------------------------


//--------------------------------------
//Output text temperature and humidity to to serial
//--------------------------------------
void outPutDHT()
{
  Serial.print("Humidity: ");
  Serial.print(humidityPercent);
  Serial.println("%");
  Serial.print("Temperature: ");
  Serial.print(tempC);
  Serial.println("C");
  Serial.println("---------------------");
}
//--------------------------------------
//End text temperature and humidity to to serial
//--------------------------------------


//--------------------------------------
//Measure lux value
//--------------------------------------
float measureLux()
{
  /* Get a new sensor event */
  sensors_event_t event;
  tsl.getEvent(&event);

  /* Display the results (light is measured in lux) */
  if (event.light)
  {
    return event.light;
  }
  else
  {
    /* If event.light = 0 lux the sensor is probably saturated
       and no reliable data could be generated! */
    Serial.println("Sensor overload");
    return -1;
  }
}
//--------------------------------------
//End measure lux value
//--------------------------------------


//--------------------------------------
//Detect motion
//--------------------------------------
int detectMotion()
{
  int pirState = LOW;         // we start, assuming no motion detected
  int motionStatus = LOW;       // variable for reading the pin status
  //give it time to detect motion
  delay(1000);
  //get the status
  motionStatus = digitalRead(PIRPIN); 
  //set variable
  if (motionStatus == HIGH) 
  {            
      pirState = HIGH;
  } 
  return pirState;
}
//--------------------------------------
//End detect motion
//--------------------------------------



//--------------------------------------
//Autoconfiguration for lux sensor
//--------------------------------------
void configureSensor(void)
{

  /* You can also manually set the gain or enable auto-gain support */
  // tsl.setGain(TSL2561_GAIN_1X);      /* No gain ... use in bright light to avoid sensor saturation */
  // tsl.setGain(TSL2561_GAIN_16X);     /* 16x gain ... use in low light to boost sensitivity */
  tsl.enableAutoRange(true);            /* Auto-gain ... switches automatically between 1x and 16x */

  /* Changing the integration time gives you better sensor resolution (402ms = 16-bit data) */
  //tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_13MS);      /* fast but low resolution */
  tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_101MS);  /* medium resolution and speed   */
  // tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_402MS);  /* 16-bit data but slowest conversions */

  /* Update these values depending on what you've set above! */
  Serial.println("------------Lux config--------------");
  Serial.print  ("Gain:         "); Serial.println("Auto");
  Serial.print  ("Timing:       "); Serial.println("101 ms");
  Serial.println("------------------------------------");
}
//--------------------------------------
//End autoconfiguration for lux sensor
//--------------------------------------


//--------------------------------------
//Get datetime as a readable string
//--------------------------------------
String dateTime()
{
  //get the current time
  currentTime = rtc.now();

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
  return output;
}
//--------------------------------------
//End get datetime as a readable string
//--------------------------------------

