#include <EngduinoLEDs.h>
#include <EngduinoLight.h>
#include <EngduinoThermistor.h>

/**
 * Measures how the temperature changes with light, and sends
 * this data back through a serial connection
 */

const int T_BLUE = 10;
const int T_RED = 30;
const int T_RANGE = (T_RED - T_BLUE);
const int LIGHT_SENSOR_CHANNEL = 4;// The light sensor is channel 4

unsigned long lightValue, previousLightValue = 0;
float temperatureValue, previousTemperature = 0;

void setup()
{
  EngduinoLEDs.begin();
  EngduinoLight.begin();
  EngduinoThermistor.begin();
  Serial.begin(9600);
}

void loop() { 
  lightValue = calculateLightValue();
  
  float temperatureValue = getTemperature();
  
  if (lightValue != previousLightValue || temperatureValue != previousTemperature) {
    sendData(lightValue, temperatureValue);
  }
  
  int colour[2];
  calculateColour(colour, temperatureValue);
  
  // Divide the light value between the 16 LEDs (1024 / 16 = 64)
  int lastLED = lightValue / 64;
  for (int i = 0; i < lastLED; i++) {
    EngduinoLEDs.setLED(i, colour[0], 0, colour[1]);
  }
  for (int i = lastLED; i < 16; i++) {
    EngduinoLEDs.setLED(i, OFF);
  }
  
  previousLightValue = lightValue;
  previousTemperature = temperatureValue;
  delay(1000);
}

/**
 * Sends the data through a serial connection in the format `light,temperature`
 */
void sendData(unsigned long lightValue, float temperatureValue) {
  Serial.print(lightValue);
  Serial.print(",");
  Serial.print(temperatureValue);
  Serial.print("\n");
}

/**
 * Determines the colour based on temperature
 */
void calculateColour(int colour[], int temperatureValue) {
  colour[0] = (constrain(temperatureValue - T_BLUE, 0, T_RANGE) * MAX_BRIGHTNESS) / T_RANGE;
  colour[1] = (constrain(T_RED - temperatureValue,  0, T_RANGE) * MAX_BRIGHTNESS) / T_RANGE;
}

/**
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
