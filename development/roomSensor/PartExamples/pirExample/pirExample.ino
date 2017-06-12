//https://learn.adafruit.com/pir-passive-infrared-proximity-motion-sensor/connecting-to-a-pir
//https://learn.adafruit.com/pir-passive-infrared-proximity-motion-sensor/using-a-pir


const int ledPin = 13;                // choose the pin for the LED
const int PIRPIN = 4;               // choose the input pin (for PIR sensor)
int pirState = LOW;             // we start, assuming no motion detected
int motionStatus = 0;                    // variable for reading the pin status
 
void setup() 
{
  pinMode(ledPin, OUTPUT);      
  pinMode(PIRPIN, INPUT);     
 
  Serial.begin(9600);
}
 
void loop()
{
  motionStatus = digitalRead(PIRPIN); 
  if (motionStatus == HIGH) 
  {            // check if the input is HIGH
    digitalWrite(ledPin, HIGH);  // turn LED ON
    if (pirState == LOW) 
    {
      // we have just turned on
      Serial.println("Motion detected");
      // We only want to print on the output change, not state
      pirState = HIGH;
    }
  } 
  else 
  {
    digitalWrite(ledPin, LOW); // turn LED OFF
    if (pirState == HIGH)
    {
      // we have just turned off
      Serial.println("Motion ended");
      // We only want to print on the output change, not state
      pirState = LOW;
    }
  }
}
