/* 
 * A basic blink examples for the Basic NodeMCU_V2 Dev Shield
 * 
 * This program turns on and off the RGB's blue LED (also connected 
 * to segment G). 
 * As you may be able to notice, as the shield's blue LED turns on, 
 * the LED on the NodeMCU dev board itself (the module) turns off. 
 * This is because the NodeMCU's LED and the shield's blue LED are 
 * connected together. The NodeMCU's LED is active-low (turns on when 
 * the signal to it is LOW), and the shield's LED is active-high. 
 */

#include "basic-nodemcuv2-shield.h"

void setup() {
  pinMode(SHIELD_LEDB, OUTPUT);
}

// The loop function runs over and over again forever
void loop() {
  digitalWrite(SHIELD_LEDB, HIGH);
  delay(1000);
  digitalWrite(SHIELD_LEDB, LOW);
  delay(1000);
}
