//LDR pin
const int LDRPIN = A2;

void setup() 
{
  //start serial for seial debugging
  Serial.begin(9600);
}

void loop()
{
  //get the light reading
  int light = analogRead(LDRPIN);
  //output light reading on serial
  Serial.println(light);
  //wait for three seconds
  delay(3000);
}
