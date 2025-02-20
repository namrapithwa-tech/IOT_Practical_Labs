/*
 * This ESP8266 NodeMCU code was developed by newbiely.com
 *
 * This ESP8266 NodeMCU code is made available for public use without any restriction
 *
 * For comprehensive instructions and wiring diagrams, please visit:
 * https://newbiely.com/tutorials/esp8266/esp8266-sound-sensor
 */

#define SENSOR_PIN D7 // The ESP8266 pin D7 connected to the OUT pin of the sound sensor

int prev_state = HIGH;  // The previous state from the input pin
int sound_state;        // The current reading from the input pin
unsigned long prev_time = 0;  // Previous timestamp for frequency measurement
unsigned int transitions = 0; // Count of state changes
const unsigned int interval = 1000; // Measurement interval in milliseconds

void setup() {
  // Initialize the Serial to communicate with the Serial Monitor.
  Serial.begin(9600);
  // initialize the ESP8266's pin as an input
  pinMode(SENSOR_PIN, INPUT);
}

void loop() {
  // Read the current state of the ESP8266's input pin
  sound_state = digitalRead(SENSOR_PIN);

  // Check for a state transition (HIGH to LOW or LOW to HIGH)
  if (sound_state != prev_state) {
    transitions++; // Increment the transition count
    prev_state = sound_state; // Update the previous state
  }

  // Measure the frequency every 1 second (1000 ms)
  if (millis() - prev_time >= interval) {
    // Calculate the frequency in Hz (transitions / 2 because a full cycle is HIGH + LOW)
    float frequency = transitions / 2.0;

    // Print the sound state and frequency
    Serial.print("The sound has been detected: Sound State: ");
    Serial.print(sound_state);
    Serial.print(", Frequency: ");
    Serial.print(frequency);
    Serial.println(" Hz");

    // Reset counters and timestamp
    transitions = 0;
    prev_time = millis();
  }
}
