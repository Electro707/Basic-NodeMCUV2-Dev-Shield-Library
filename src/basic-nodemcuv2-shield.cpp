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
