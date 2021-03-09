/* 
 * A basic analogWrite for the Basic NodeMCU_V2 Dev Shield
 * 
 * This program, incrementally, fades each segment out of the 
 * 7-segment display on then off.
 * 
 */

#include "basic-nodemcuv2-shield.h"

// Define the total number of segments (so we can used them in a for loop)
#define SEGMENT_AMOUNT 7
// Define the delay time when incremement the PWM duty cycle
#define DELAY_TIME 5
// Create an array with all segments (so we can used them in a for loop)
uint8_t segments[] = {SHIELD_SEGA, SHIELD_SEGB, SHIELD_SEGC, SHIELD_SEGD, SHIELD_SEGE, SHIELD_SEGF, SHIELD_SEGG};

void setup() {
  // Set all segments as output
  for(int i=0;i<SEGMENT_AMOUNT;i++){
    pinMode(segments[i], OUTPUT);
  }
  // Change the analog write range to 0->255
  analogWriteRange(255);
}

// The loop function runs over and over again forever
void loop() {
  // For each segment in the 7-segment display
  for(int i=0;i<SEGMENT_AMOUNT;i++){
    // Fade the segment into fully ON
    for(int p=0;p<255;p++){
      analogWrite(segments[i], p);
      delay(DELAY_TIME);
    }
    // Fade the same segment into fully OFF
    for(int p=254;p>=0;p--){
      analogWrite(segments[i], p);
      delay(DELAY_TIME);
    }
  }
} 
