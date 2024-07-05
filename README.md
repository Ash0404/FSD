# Food Spoilage Detection System

## Overview

The Food Spoilage Detection System is an IoT-based project designed to monitor the spoilage of food using sensors and notify users via the Blynk IoT platform. The system uses the MQ-6 gas sensor to detect the presence of gases produced by spoiling food and the DHT11 sensor to monitor temperature and humidity. The ESP8266 microcontroller is used to process the sensor data and communicate with the Blynk IoT platform to provide real-time updates to users.

## Components

- **MQ-6 Gas Sensor**: Detects the presence of gases such as methane and butane, which are commonly produced by spoiling food.
- **DHT11 Temperature and Humidity Sensor**: Monitors the ambient temperature and humidity, which are critical factors affecting food spoilage.
- **ESP8266**: Microcontroller used for processing sensor data and connecting to the internet.
- **Blynk IoT Platform**: Provides real-time notifications and data visualization to users through a mobile app.

## Features

- **Real-time Monitoring**: Continuously monitors gas levels, temperature, and humidity.
- **Threshold Alerts**: Sends notifications when gas levels, temperature, or humidity exceed predefined thresholds.
- **Data Logging**: Logs sensor data for historical analysis and trends.
- **User-Friendly Interface**: Uses the Blynk app for easy access to real-time data and alerts.

## Setup Instructions

1. **Hardware Setup**:
   - Connect the MQ-6 gas sensor to the ESP8266.
   - Connect the DHT11 sensor to the ESP8266.
   - Ensure the ESP8266 is connected to a power source.

2. **Software Setup**:
   - Install the Arduino IDE.
   - Install the necessary libraries: `ESP8266WiFi`, `BlynkSimpleEsp8266`, `DHT`.
   - Create a new project in the Blynk app and obtain the authentication token.
   - Update the Arduino sketch with your WiFi credentials and Blynk authentication token.
   - Upload the Arduino sketch to the ESP8266.

3. **Configuration**:
   - Set threshold values for gas levels, temperature, and humidity in the Arduino sketch.
   - Configure the Blynk app to display sensor data and send notifications.

## Usage

- Open the Blynk app to monitor real-time data from the sensors.
- Receive notifications on your mobile device when sensor readings exceed predefined thresholds.
- Analyze logged data to understand the conditions leading to food spoilage.

## Code

```cpp
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
```
