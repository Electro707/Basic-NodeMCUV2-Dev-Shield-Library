/* 
 * A temperature sensor readout example for the Basic NodeMCU_V2 Dev Shield
 * 
 */

#include "basic-nodemcuv2-shield.h"

// IMPORTANT:
// If the dev board doesn't use an LM35 (check the marking on the TO-92
// package), then comment out the LM35 line (by adding // to the beginning
// of it) and un-comment the right temperature sensor (by removing the //
// in the beginning of it).
//LM35 temp_sensor;
LM36 temp_sensor;

// Internal variables
float temp_c, temp_f;

void setup() {
  // Use the library function to set the proper pinmode
  shieldSetPinout();
  Serial.begin(115200);
  Serial.println("Welcome to the E707 Basic NodeMCU-V2 Shield Temperature Example");
}

// The loop function runs over and over again forever
void loop() {
  temp_c = temp_sensor.getTemperatureC();
  temp_f = temp_sensor.getTemperatureF();
  Serial.print("Current Temperature is = ");
  Serial.print(temp_c); Serial.print(" C, ");
  Serial.print(temp_f); Serial.println("F");
  delay(1000);
}
