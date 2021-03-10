// THIS EXAMPLES IS A WORK-IN-PROGRESS!!!
// PLEASE DON'T USE THIS YET
/** 
 *  Serial Command Examples for the E707 Basic NodeMCU-V2 Shield
 *  
 *  This program accepts a serial command to turn on or off segments and
 *  other cool stuff. The baud rate on the serial terminal should be
 *  set to 9600 if it's not.
 *  
 *  The command syntax goes as follows:
 *  - aX -> Turn on segment X (from A to G)
 *  - dX -> Turn off segment X (from A to G)
 *  - pXY -> PWM segment X (from A to G) with duty cycle Y (from 1 to 255)
 *  - v -> Read back the voltage value on the analog pin (connected to the
 *         LM34 or similar temperature sensor.
 *  - t -> Read the temperature from the on-board LM34 (or similar) 
 *         temperature sensor (connected to the analog pin)
 *  - b -> Start/Stop reporting if a button is pressed or depressed
 */ 

#include "basic-nodemcuv2-shield.h"

// Create the read buffer. We expect a maximum of 5 characters
char read_buffer[5];

int seg_pin;
int pwm_amount;

void setup(){
   // Use the library function to set the proper pinmode
   shieldSetPinout();
   // TODO: Set the analog range to 0->255
   // Start the serial terminal and print out a start message
   Serial.begin(9600);
   Serial.println("Welcome to the Serial Command Examples");
   Serial.println("Type in a command according to the syntax (see program comments) to do stuff");
}
// The infinite loop
void loop(){
 if(Serial.available()){
   int numb_read = Serial.readBytesUntil('\n', read_buffer, 5);
   // Just in case, handle when there is no data 
   if(numb_read != 0){
     switch(read_buffer[0]){
      case 'a':
      case 'A':
        seg_pin = get_segment_pin(read_buffer[1]);
        if(seg_pin == -1){break;}   // Don't procede if the pin is invalid
        digitalWrite(seg_pin, HIGH);
        break;
      case 'd':
      case 'D':
        seg_pin = get_segment_pin(read_buffer[1]);
        if(seg_pin == -1){break;}   // Don't procede if the pin is invalid
        digitalWrite(seg_pin, LOW);
        break;
      case 'p':
      case 'P':
        seg_pin = get_segment_pin(read_buffer[1]);
        if(seg_pin == -1){break;}   // Don't procede if the pin is invalid
        pwm_amount = strtol(&read_buffer[2], NULL, 10);
        // TODO: Add PWM data validation
        analogWrite(seg_pin, pwm_amount);
        break;
     }
   }
 }
}

// Function that we give it a segment text (like 'a' or 'D')
// and returns the pin number which it's connecte to.
// Function also prints out an error message if the segment 
// text is incorrect
//
int get_segment_pin(char segment_text){
  switch(segment_text){
    case 'a':
    case 'A':
      return SHIELD_SEGA;
    case 'b':
    case 'B':
      return SHIELD_SEGB;
    case 'c':
    case 'C':
      return SHIELD_SEGC;
    case 'd':
    case 'D':
      return SHIELD_SEGD;
    case 'e':
    case 'E':
      return SHIELD_SEGE;
    case 'f':
    case 'F':
      return SHIELD_SEGF;
    case 'g':
    case 'G':
      return SHIELD_SEGG;
    default:
      Serial.println("Invalid Segment Character");
      // Nothing matches, so we returns nothing
      return -1;
  }
}
