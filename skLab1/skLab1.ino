// C++ code
//
void setup()
{
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);
}

void loop()
{
  digitalWrite(D5, HIGH);
  delay(250);
  digitalWrite(D5, LOW);
  delay(250);
  
  digitalWrite(D6, HIGH);
  delay(250);
  digitalWrite(D6, LOW);
  delay(250);
  
  digitalWrite(D7, HIGH);
  delay(250);
  digitalWrite(D7, LOW);
  delay(250); //Wait for 1000 milisecond(s)
}