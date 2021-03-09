/**
 * Basic NodeMCU_V2 Development Shield Library
 * By Electro707
 * 
 * This "library" is mostly to provide pin definitions and some examples
 * for the Basic NodeMCU_V2 Development Shield
 * 
 */
#ifndef BASIC_NODEMCU_V2_DEV_SHIELD
#define BASIC_NODEMCU_V2_DEV_SHIELD

// This library should only be included if using a NodeMCU V2 (as it's for
// keyword definitions and examples. We can't directly check if the board
// is specifically a V2, but we can do the next best thing and check if it's
// a NodeMCU at all.
#if !defined(ARDUINO_ESP8266_NODEMCU)
#error Only the NodeMCU V2 board is supported for this program
#endif

// Define the 7-segment pins
#define SHIELD_SEGA 15
#define SHIELD_SEGB 13
#define SHIELD_SEGC 12
#define SHIELD_SEGD 4
#define SHIELD_SEGE 0
#define SHIELD_SEGG 2
#define SHIELD_SEGF 14
// Define the RGB LED's pins
#define SHIELD_LEDR SHIELD_SEGA
#define SHIELD_LEDG SHIELD_SEGD
#define SHIELD_LEDB SHIELD_SEGG
// Define the button's pins
#define SHIELD_BT1 16
#define SHIELD_BT2 5
#define SHIELD_BT3 10

#endif
