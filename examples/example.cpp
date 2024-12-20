#include "shiftregdriver.h"

shiftregdriver shiftreg( 2, 3, 4 ); // Data pin, Shift Reg clock, Latch clock

const uint8_t num[10] = {

    NUM_8_LSB_0,
    NUM_8_LSB_1,
    NUM_8_LSB_2,
    NUM_8_LSB_3,        // *
    NUM_8_LSB_4,        // * These are included in the library
    NUM_8_LSB_5,        // *
    NUM_8_LSB_6,
    NUM_8_LSB_7,
    NUM_8_LSB_8,
    NUM_8_LSB_9

};

// by typing apb <- put a letter here.
// ex.. apba ( with intellisense itll probably show )
// APB_8_LSB_A <- has prebuilt segment in bit (8bit)

// uncomment these for example. one at a time!

// #define apb_test_no_printstr
//#define apb_test_printstr

extern "C" void app_main() {

    shiftreg.begin( 0 );
    shiftreg.ssegc( 4 );    // <- check the library folder for wokwi diagram and toml. ( please also theres a  )

    #ifndef apb_test_printstr
    #ifndef apb_test_no_printstr
    /**
     * prints 0 - 9 with clear
     * 
     */
    while (1)
    {
        for ( int i = 0; i < ( sizeof( num ) / sizeof( uint8_t ) ); i++ )
        {
            shiftreg.writel( num[ i ] );
            vTaskDelay( 1000 );
            shiftreg.clear();
        }
    }
    #endif
    #endif

    #ifdef apb_test_no_printstr
    shiftreg.writel( APB_8_LSB_A, 1 );  // prints one at a time. with auto latch and no reset. continous write, on the otherhand the write doesnt have this feature
    #endif

    #ifdef apb_test_printstr
    shiftreg.printstr( "abcd", 1 );     // automatically converts each char to shift reg bits... alphabets are limited due to 7-seg display limitations. ex. letter M
    #endif

}