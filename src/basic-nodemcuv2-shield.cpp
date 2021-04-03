/**
 *
 */ 

#include <basic-nodemcuv2-shield.h>

void _shieldWriteAllSegments(uint8_t output);

// Internal lookup table to each segment to a digit
uint8_t digit_to_segment[] = {
    0b00111111,
    0b00000110,
    0b01011011,
    0b01001111,
    0b01100110,
    0b01101101,
    0b01111101,
    0b00000111,
    0b01111111,
    0b01101111
};

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

// Function to display a digit on the onboard 7 segment display
void shieldDisplayDigit(int digit){
  if(digit > 9 || digit < 0){
    return;
  }
  _shieldWriteAllSegments(digit_to_segment[digit]);
}

/**
 * Internal function to write all segment's output by a 8-bit number (each bit
 * indicating which segment is off or on)
 */
void _shieldWriteAllSegments(uint8_t output){
  uint8_t shield_segments[] = {SHIELD_SEGA, SHIELD_SEGB, SHIELD_SEGC, SHIELD_SEGD, SHIELD_SEGE, SHIELD_SEGF, SHIELD_SEGG};
  for(uint8_t i=0;i<7;i++){
    digitalWrite(shield_segments[i], output & (1 << i));
  }
}

// Function to read the temperature of a temp-sensor and return
// it in Celcius
float _TempSensor::getTemperatureC(void){
    int adc_voltage = analogRead(A0);
    // Assume 3.3v is the max range
    float voltage_mv = adc_voltage * 3300 / 1024;
    float temp_c = (voltage_mv - offset) / divide_by;
    return temp_c;
}

// Function to read the temperature of a temp-sensor and return
// it in Fahrenheit
float _TempSensor::getTemperatureF(void){
    float temp_c = getTemperatureC();
    float temp_f = temp_c * 1.8 + 32;
    return temp_f;
}
