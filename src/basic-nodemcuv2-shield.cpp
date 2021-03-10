/**
 *
 */ 

#include <basic-nodemcuv2-shield.h>

// Function to set all relative IO's as input or output
void shieldSetPinout(void){
    // Set all segments as outputs
    pinMode(SHIELD_SEGA, OUTPUT);
    pinMode(SHIELD_SEGB, OUTPUT);
    pinMode(SHIELD_SEGC, OUTPUT);
    pinMode(SHIELD_SEGD, OUTPUT);
    pinMode(SHIELD_SEGE, OUTPUT);
    pinMode(SHIELD_SEGF, OUTPUT);
    pinMode(SHIELD_SEGG, OUTPUT);
    // Set all buttons as input
    pinMode(SHIELD_BT1, INPUT);
    pinMode(SHIELD_BT2, INPUT);
    pinMode(SHIELD_BT3, INPUT);
}
