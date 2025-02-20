#include<SoftwareSerial.h>
String mystr = "Hello ANONYMOUS";
const int rxPin = D0;
const int txPin = D1;
SoftwareSerial mySerial(rxPin,txPin);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  mySerial.begin(9600);
  pinMode(D1, INPUT);
  pinMode(D0, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  String readstr,mystr;
  mystr = Serial.readString();
  mySerial.print(mystr);
  if(mySerial.available()>0){
    readstr = mySerial.readString();
    Serial.println(readstr);
  }
  delay(1000);
}
