#include <EngduinoLEDs.h>
#include <EngduinoLight.h>
#include <EngduinoThermistor.h>

// Measures how the temperature changes with light

// The light sensor is channel 4
const int LIGHT_SENSOR_CHANNEL = 4;
unsigned long previousLightValue = 0;
float previousTemperature = 0;

void setup()
{
  EngduinoLEDs.begin();
  EngduinoLight.begin();
  EngduinoThermistor.begin();
  Serial.begin(9600);
}

void loop() { 
  unsigned long lightValue = calculateLightValue();
  float temperature = getTemperature();
  
  if (lightValue != previousLightValue || temperature != previousTemperature) {
    Serial.print(lightValue);
    Serial.print(",");
    Serial.print(temperature);
    Serial.print("\n");
  }
  
  previousLightValue = lightValue;
  previousTemperature = temperature;
  
  // We want to be more sensitive to low light
  int lastLED = lightValue / 64;
  for (int i = 0; i < lastLED; i++) {
    EngduinoLEDs.setLED(i, WHITE, 2);
  }
  for (int i = lastLED; i < 16; i++) {
    EngduinoLEDs.setLED(i, OFF);
  }
  
  delay(500);
}

/*
* Calculates the light level based on data from the light sensor
* Returns light level ranged 0 - 1023
*/
unsigned long calculateLightValue() {
  // Take an average of 100 readings of the analogue input
  unsigned long light = 0;
  for (int i = 0; i < 100; i++) {
  	light += analogRead(LIGHT_SENSOR_CHANNEL);
  }
  return light / 100;
}

float getTemperature() {
  return EngduinoThermistor.temperature();
}
