#include "DHT.h"
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>


char auth[] = "phpkHIAVM5uLB8j6pRcbDlGiK7rvlYsa";
char ssid[] = "Shaik's m32";
char pass[] = "1234567890";

BlynkTimer timer;

#define DHTPIN D4   // what digital pin we're connected to

// Uncomment whatever type you're using!
#define DHTTYPE DHT11  // DHT 11
//#define DHTTYPE DHT22  // DHT 22 (AM2302), AM2321
//#define DHTTYPE DHT21  // DHT 21 (AM2301)

DHT dht(DHTPIN, DHTTYPE);

int smokeA0 = A0;

// Your threshold value. You might need to change it.
int sensorThres = 6;

void FSDSensor() {
  // Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();

  int analogSensor = analogRead(smokeA0);

  Serial.print(" Humidity: ");
  Serial.print(h);
  Blynk.virtualWrite(V1,h);
  Serial.print(" % ");
  Serial.print("Temperature: ");
  Serial.print(t);
  Blynk.virtualWrite(V0,t);
  Serial.print(" *C ");
  Serial.print(" Pin A0: ");
  Serial.print(analogSensor);
  Blynk.virtualWrite(V2,analogSensor);


  int analogSensor = analogRead(smokeA0);

  Serial.print(" Humidity: ");
  Serial.print(h);
  Blynk.virtualWrite(V1,h);
  Serial.print(" % ");
  Serial.print("Temperature: ");
  Serial.print(t);
  Blynk.virtualWrite(V0,t);
  Serial.print(" *C ");
  Serial.print(" Pin A0: ");
  Serial.print(analogSensor);
  Blynk.virtualWrite(V2,analogSensor);


  // Checks if it has reached the threshold value
  if (analogSensor > sensorThres && h > 70 && t > 35 ) {
    Blynk.logEvent("SPOILAGE ALERT","The food is Inedible.");
    Serial.println("Food is Spoiled.");
  } else {
    Serial.println("Food is Good.");
  }

  // Check if any DHT reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println("DHT failed to read this time");
    return;
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(smokeA0, INPUT);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, FSDSensor);
  dht.begin();
  Serial.println("DHT11 test!");
}

void loop(){
 
  Blynk.run();
  timer.run();
}
