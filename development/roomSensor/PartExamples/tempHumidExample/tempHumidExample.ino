//
// An example program to extract temperature and humidity using a DHT22 sensor
//

//https://learn.adafruit.com/dht/connecting-to-a-dhtxx-sensor

//!!! IMPORTANT !!! :
//The Adafruit DHT22 library must be installed. 
//The Adafruit Unified Sensor lbrary must be installed.
//There should be a 10KOhm resistor between the data pin and 5V DCC.

#include <DHT.h>

//set the data pin
#define DHTPIN 8

//set the DHT type 
#define DHTTYPE DHT22 

float humidity;
float tempC;
float feelsLike;

//instantiate dht
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  //delay between readings
  delay(5000);

  readSensor();
  
  // Check if any reads failed and exit early (to try again).
  if (isnan(humidity) || isnan(tempC)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  outPut();
}

//gets values from sensor
void readSensor()
{
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  humidity = dht.readHumidity();
  // Read temperature as Celsius (the default)
  tempC = dht.readTemperature();
    // Compute heat index in Celsius (isFahreheit = false)
  feelsLike = dht.computeHeatIndex(tempC, humidity, false);
}

//outputs to serial
void outPut()
{
  Serial.print("Humidity: ");
  Serial.print((String)humidity);
  Serial.println("%");
  Serial.print("Temperature: ");
  Serial.print(tempC);
  Serial.println("C");
  Serial.print("Feels like: ");
  Serial.print(feelsLike);
  Serial.println("C");
  Serial.println("---------------------");
}

