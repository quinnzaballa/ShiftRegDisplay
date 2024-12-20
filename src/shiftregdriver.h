/**
 *  This library is responsible to control the shift registers...
 * Technically this automatically supports SN74HC595..
 * 
 *  If you have to use other shift reg rather than this code 
 * supports, you might need to add delay timings if needed.
 * 
 * ( Somehow this would work on most shift regs )
 * 
 *  This code only works on C++ and esp32's
 */

//--------------------------------------------------------------------------------------//
//                          AUTHOR : QUINN MATTHEW C. ZABALLA                           //
//--------------------------------------------------------------------------------------//

//--------------------------------------------------------------------------------------//
//                                                                                      //
//                                SHIFT REGISTER DRIVER                                 //
//                                                                                      //
//--------------------------------------------------------------------------------------//

// ------------------------------------------------------ //
// ----------------- INCLUDE ( LIBRARY ) ---------------- //
// ------------------------------------------------------ //

// Extra libraries ( Not in used )
#include <string>
#include <cstring>
#include "shiftregdriver_t.h"       // typedef's and etc

// FreeRTOS ( not important )
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

// drivers
#include "driver/gpio.h"

// set 1 and 0 defiend as high and low
#ifndef HIGH
#define HIGH 1
#endif
#ifndef LOW
#define LOW 0
#endif


// ------------------------------------------------------ //
// ------------ SHIFT REGISTER MAIN ( CLASS ) ----------- //
// ------------------------------------------------------ //

class shiftregdriver {
    // shiftregdriver | class | start //
//  **************************************************************************************

    // shiftregdriver | private | start // ####****####
private :
    
    // ### Other global variables ###

    gpio_config_t sr_gpio_conf_input;       // input pins   /** different configs has no importance but would still be implemented */ 
    gpio_config_t sr_gpio_conf_clk;         // clk pins       *
    
    const char* TAGSRPR = "ShiftREG: ";         // shift register tag on printf's
    
    // ### Structures ###

    struct GPIO_PINOUT_INI // Structure for gpio setup for lazy people
    {

        uint16_t DIN;           // Serial Data in
        uint16_t RCLK;          // Latch Clock
        uint16_t SRCLK;         // Serial Clock
        uint16_t SRCLK_RPIN;    // Serial Clock Reset pin ( Really not important )
                                /*  if wasnt defined or no given. Then put -1 / NC ( No Connection ) */
        // TODO Soon to implement
        /*
        uint16_t OE_PIN;         // Output Enable pin
        uint16_t OE_SRSEL;       // Output Enable ID ( Shift Register id )
        */
    };
    GPIO_PINOUT_INI _GPIO_PINOUT_INI;
    
    //  --------------------------------------------------------------------------------------

    // ### variables ###

    bool ini = false;           // Tells code if it was initialized and the gpio pins are set.
    bool rpin_set = false;      // Tells code if reset pin is enabled.
    uint sseg_count = 1;        // defaulted to 1 display

    // shiftregdriver | private | end   // ####****####

//  --------------------------------------------------------------------------------------
       
    // shiftregdriver | public  | start // ####****####
public:
    
    // --------------------- CONSTRUCTOR -------------------- //

    shiftregdriver( uint16_t DIN, uint16_t SRCLK, uint16_t RCLK );                          // normal without Reset Pin
    shiftregdriver( uint16_t DIN, uint16_t SRCLK, uint16_t RCLK, uint16_t SRCLK_RPIN );     // normal with Reset Pin

    /**
     * @brief Sets the gpio and initialized.
     * 
     * @param manual_ovr if set to 1 / ( true ) this will override and wont set the gpio automatically
     * 
     * @note
     * This begin has 2 state.
     * 
     * override ( 1 ) = tells the initializer you set the gpio yourself.
     * 
     * default  ( 0 ) = tells the initializer to set the gpio automatically.
     */
    void begin( bool manual_ovr );

//  **************************************************************************************

    // --------------------- WRITE ONLY --------------------- //
    /**
     * @brief write the bits ( 8bit in length )... ( write only once each time. non-reset type )
     * 
     * @param D_array Data array, input the binary in 8bit.
     * 
     * @note
     * Theres an option after D_array. but defaulted to ( 1 "true" )
     * 
     * This allows you to change the write method ( (1)lsb "Least Signifact Bits" / (0)msb "Most Signifact Bits" ) 
     */
    void write( uint8_t D_array );

    /**
     * @overload
     * 
     * @brief set lsb to 0 to write in msb ( write only once each time. non-reset type )
     */
    void write( uint8_t D_array, bool lsb );

//  **************************************************************************************

    // --------------- WRITE AND LATCH (AUTO) --------------- //
    /**
     * @brief write the bits and handle latch automatically ( 8bit in length )... ( write only once each time. non-reset type )
     * 
     * @param D_array Data array, input the binary in 8bit.
     * 
     * @note
     * Theres an option after D_array. but defaulted to ( 1 "true" )
     * 
     * This allows you to change the write method ( (1)lsb "Least Signifact Bits" / (0)msb "Most Signifact Bits" ) 
     */
    void writel( uint8_t D_array);

    /**
     * @overload
     * 
     * @brief set lsb to 0 to write in msb ( write only once each time. non-reset type )
     */
    void writel( uint8_t D_array, bool lsb );

//  **************************************************************************************

    // -------------------- PRINT STRING -------------------- //
    /**
     * @brief print string or text to the 7seg display
     * 
     */
    void printstr( const char* string, bool lsb );


//  **************************************************************************************

    // ------------------ 7-SEGMENT COUNTS ------------------ //
    /**
     * @brief Tells the code how many 7seg is available or shift register(s)
     * 
     * @param count how many shiftreg
     * 
     */
    void ssegc( uint8_t count );

    /**
     * ex.
     * Cname.ssegcl( 2 ); <- should be set after begin();
     * 
     */
    
//  **************************************************************************************

    /**
     * @brief clear all bits in shift register(s) ( use clearOE if applicable ) <- Soon to implement
     * 
     */
    void clear();

//  **************************************************************************************

// constructive...
    /**
     * @brief write to shift register with formatting...
     *
     * @param format format to be done usually in string format..
     *
     * @param ... format indentifiers
     *
     */
    void printstrf(const char* format, ...);

    // shiftregdriver | public  | end   // ####****####

//  **************************************************************************************
    // shiftregdriver | class | end //
};