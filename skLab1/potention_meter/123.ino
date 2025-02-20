/*************************************************************
  This is a simple demo of sending and receiving some data.
  Be sure to check out other examples!
 *************************************************************/

/* Fill-in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID "TMPL3GKiH3Y4M"
#define BLYNK_TEMPLATE_NAME "Quickstart Template"
#define BLYNK_AUTH_TOKEN "GkRVmkOeQ-9rHjqk-E3dlzyp6rgOB1ZU"

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char ssid[] = "Akshat_NP"; // Your WiFi SSID
char pass[] = "Akshat#23"; // Your WiFi password

BlynkTimer timer;

// This function is called every time the Virtual Pin 0 state changes
BLYNK_WRITE(V0)
{
  int value = param.asInt(); // Read the incoming value
  digitalWrite(D4, value);  // Set D4 pin according to value
  Blynk.virtualWrite(V1, value); // Update Virtual Pin V1
}

// This function is called every time the device is connected to Blynk.Cloud
BLYNK_CONNECTED()
{
  Blynk.setProperty(V3, "offImageUrl", "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations.png");
  Blynk.setProperty(V3, "onImageUrl", "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations_pressed.png");
  Blynk.setProperty(V3, "url", "https://docs.blynk.io/en/getting-started/what-do-i-need-to-blynk/how-quickstart-device-was-made");
}

// This function sends Arduino's uptime every second to Virtual Pin 2
void myTimerEvent()
{
  Blynk.virtualWrite(V2, millis() / 1000); // Send uptime in seconds
}

void setup()
{
  Serial.begin(9600); // Start the serial monitor
  pinMode(D4, OUTPUT); // Set D4 as an output pin

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass); // Connect to Blynk Cloud

  timer.setInterval(1000L, myTimerEvent); // Call myTimerEvent every second
}

void loop()
{
  Blynk.run(); // Run Blynk
  timer.run(); // Run the timer
}
