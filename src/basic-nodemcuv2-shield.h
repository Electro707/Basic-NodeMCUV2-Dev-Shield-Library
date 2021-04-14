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

#include <Arduino.h>

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

/**
 * \brief Set the pin mode (INPUT or OUTPUT) for all relavent pins for the shield's periferals.
 */
void shieldSetPinout(void);

/**
 * \brief Set a digit (between 0 and 9) on the 7 segment display of the shield.
 * \param digit The digit to display, between 0 and 9.
 * 
 * Example:
 * \code
 * #include "basic-nodemcuv2-shield.h"
 * void setup(){
 *   shieldSetPinout();
 * }
 * void loop(){
 *    // Display a 6 on the 7-segment display
 *    shieldDisplayDigit(6);
 *    delay(500);
 *    // Display a 9 on the 7-segment display
 *    shieldDisplayDigit(9);
 * }
 * \endcode
 */
void shieldDisplayDigit(int digit);

/**
 * \brief Base class for any temperature sensor. Temp sensors call up this class and
 * change the offset and divide_by variables. This should eliminate copy-and-paste
 * code
 */
class _TempSensor{
    public:
        /**
         * \brief Function to read the temperature of a temp-sensor and return it in Celcius
         * \return The temperature in Celcius
         */
        float getTemperatureC(void);
         /**
         * \brief Function to read the temperature of a temp-sensor and return it in Fahrenheit
         * \return The temperature in Fahrenheit
         */
        float getTemperatureF(void);
    protected:
        /**
         * \brief The voltage offset in mV from the temperature sensor
         * 
         * This number is substracted from the read analog input value (in mV) before dividing by \ref divide_by.
         */
        int offset;
        /**
         * \brief The voltage division in mV from the temperature sensor
         * 
         * This number is what the input voltage in mV is divided by after substracting \ref offset.
         */
        int divide_by;
};

/**
 * \brief The LM35 temp-sensor class
 * \details A class to read the temperature from an LM35 temperature sensor. 
 * \see See the _TempSensor documentation for how to use this class
 */
class LM35: public _TempSensor{
    public:
        LM35(){
            offset = 0;
            divide_by = 10;
        }
};

/**
 * \brief The LM36 temp-sensor class
 * \details A class to read the temperature from an LM36 temperature sensor. 
 * \see See the _TempSensor documentation for how to use this class
 */
class LM36: public _TempSensor{
    public:
        LM36(){
            offset = 500;
            divide_by = 10;
        }
};

#endif
