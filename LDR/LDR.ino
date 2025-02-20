/*
 * This ESP8266 NodeMCU code was developed by newbiely.com
 *
 * This ESP8266 NodeMCU code is made available for public use without any restriction
 *
 * For comprehensive instructions and wiring diagrams, please visit:
 * https://newbiely.com/tutorials/esp8266/esp8266-ldr-module
 */

#define LDR_PIN D0 // ESP8266's pin connected to the DO pin of the LDR module

unsigned long currentMillis = 0;
unsigned long previousMillis = 0;
const unsigned long interval = 500; // Time interval to check light changes

void setup() {
  // Initialize the Serial to communicate with the Serial Monitor.
  Serial.begin(9600);

  // Initialize the ESP8266's pin as an input
  pinMode(LDR_PIN, INPUT);
}

void loop() {
  // Read the digital value from the LDR module
  int lightState = digitalRead(LDR_PIN);

  // Use a timer to check light intensity dynamically
  currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    // Output descriptive light levels
    if (lightState == LOW) {  
      Serial.println("Light Intensity: Dim - It's quite dark or low light.");
    } else {
      Serial.println("Light Intensity: Bright - The environment is well-lit.");
    }
  }
}
