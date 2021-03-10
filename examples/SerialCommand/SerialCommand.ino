/** 
 *  Serial Command Examples for the E707 Basic NodeMCU-V2 Shield
 *  
 *  This program accepts a serial command to turn on or off segments and
 *  other cool stuff. The baud rate on the serial terminal should be
 *  set to 115200 if it's not.
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

#define DEBOUNCE_DELAY 20

// IMPORTANT:
// If the dev board doesn't use an LM35 (check the marking on the TO-92
// package), then comment out the LM35 line (by adding // to the beginning
// of it) and un-comment the right temperature sensor (by removing the //
// in the beginning of it).
LM35 temp_sensor;
//LM36 temp_sensor;

// Create the read buffer. We expect a maximum of 5 characters
char read_buffer[5];

// Internal variables
int seg_pin, pwm_amount, analog_mv;
float temp_c, temp_f;
// Flag to determine if we are checking for buttons state change
bool checking_bt_press = false;
// Store the previous button pressed in an array
bool prev_bt_state[3];
// Have an array of all button's pins so we can use them in a for loop
uint8_t shield_bt_arr[] = {SHIELD_BT1, SHIELD_BT2, SHIELD_BT3};

void setup(){
   // Use the library function to set the proper pinmode
   shieldSetPinout();
   memset(prev_bt_state, 0, 3);
   // Set the "analog" write range to 0->255
   analogWriteRange(255);
   // Start the serial terminal and print out a start message
   Serial.begin(115200);
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
        if(pwm_amount < 0 || pwm_amount > 255){break;}
        analogWrite(seg_pin, pwm_amount);
        break;
      case 'v':
      case 'V':
        analog_mv = analogRead(A0);
        analog_mv = analog_mv * 3300 / 1024;
        Serial.print("Voltage Value (mV) = ");
        Serial.println(analog_mv);
        break;
      case 't':
      case 'T':
        temp_c = temp_sensor.getTemperatureC();
        temp_f = temp_sensor.getTemperatureF();
        Serial.print("Current Temperature is = ");
        Serial.print(temp_c); Serial.print(" C, ");
        Serial.print(temp_f); Serial.println("F");
        break;
      case 'b':
      case 'B':
        if(checking_bt_press == false){
          checking_bt_press = true;
          Serial.println("Started checking for button presses");
        } else {
          checking_bt_press = false;
          Serial.println("Stopped checking for button presses");
        }
        update_all_bt_state();
        break;
     }
   }
 }
 // Button checking loop
 if(checking_bt_press){
  bool bt_state;
  for(int i=0;i<3;i++){
    bt_state = digitalRead(shield_bt_arr[i]);
    if(bt_state != prev_bt_state[i]){
      prev_bt_state[i] = bt_state;
      if(bt_state){
        Serial.print("Depressed button "); Serial.println(i+1);
      } else {
        Serial.print("Pressed button "); Serial.println(i+1);
      }
      delay(DEBOUNCE_DELAY);
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

// Function that updates the previous button state to the current one.
// This is called so that when we state checking for button pressed, we
// don't immediatly get a message if the previou state is different than
// the current one
void update_all_bt_state(void){
  for(int i=0;i<3;i++){
    prev_bt_state[i] = digitalRead(shield_bt_arr[i]);
  }
}
