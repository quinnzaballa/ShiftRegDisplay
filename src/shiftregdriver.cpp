#include "shiftregdriver.h" // Main header linkage

/**
 *  This file has less information and comments than the header itself...
 * 
 *  But dont worry it would still have some comments.
 */

// ### other functions ( not part of class )

int charto8bit(char c) {

    switch ( c ) 
    {
    // ---------------------- ALPHABET ---------------------- //

        case 'A': return APB_8_LSB_A;
        case 'a': return APB_8_LSB_A;   // compensate for small letter
        case 'b': return APB_8_LSB_b;
        case 'B': return APB_8_LSB_b;   // compensate for big letter
        case 'C': return APB_8_LSB_C;
        case 'c': return APB_8_LSB_C;   // compensate for small letter
        case 'd': return APB_8_LSB_d;
        case 'D': return APB_8_LSB_d;   // compensate for big letter
        case 'E': return APB_8_LSB_E;
        case 'e': return APB_8_LSB_E;   // compensate for small letter
        case 'F': return APB_8_LSB_F;
        case 'f': return APB_8_LSB_F;   // compensate for small letter
        case 'G': return APB_8_LSB_G;
        case 'g': return APB_8_LSB_g;       // small letter of G
        case 'H': return APB_8_LSB_H;
        case 'h': return APB_8_LSB_h;       // small letter of H
        case 'I': return APB_8_LSB_I;
        case 'i': return APB_8_LSB_i;       // small letter of I
        case 'J': return APB_8_LSB_J;
        case 'j': return APB_8_LSB_j;       // small letter of J
        case 'k': return APB_8_LSB_k;
        case 'K': return APB_8_LSB_k;   // compensate for big letter
        case 'L': return APB_8_LSB_L;
        case 'l': return APB_8_LSB_L;   // compensate for small letter
        case 'n': return APB_8_LSB_n;
        case 'N': return APB_8_LSB_n;   // compensate for big letter
        case 'O': return APB_8_LSB_O;
        case 'o': return APB_8_LSB_o;       // small letter of O
        case 'P': return APB_8_LSB_P;
        case 'p': return APB_8_LSB_P;   // compensate for small letter
        case 'q': return APB_8_LSB_q;
        case 'Q': return APB_8_LSB_q;   // compensate for big letter
        case 'r': return APB_8_LSB_r;
        case 'R': return APB_8_LSB_r;   // compensate for big letter
        case 'S': return APB_8_LSB_S;
        case 's': return APB_8_LSB_S;   // compensate for small letter
        case 't': return APB_8_LSB_t;
        case 'T': return APB_8_LSB_t;   // compensate for big letter
        case 'U': return APB_8_LSB_U;
        case 'u': return APB_8_LSB_u;       // small letter of U
        case 'x': return APB_8_LSB_X;
        case 'X': return APB_8_LSB_X;   // compensate for big letter
        case 'y': return APB_8_LSB_y;
        case 'Y': return APB_8_LSB_y;   // compensate for big letter

    // ----------------------- NUMBERS ---------------------- //

        case '0': return NUM_8_LSB_0;
        case '1': return NUM_8_LSB_1;
        case '2': return NUM_8_LSB_2;
        case '3': return NUM_8_LSB_3;
        case '4': return NUM_8_LSB_4;
        case '5': return NUM_8_LSB_5;
        case '6': return NUM_8_LSB_6;
        case '7': return NUM_8_LSB_7;
        case '8': return NUM_8_LSB_8;
        case '9': return NUM_8_LSB_9;

    // ----------------------- DEFAULT ---------------------- //
        default:  return 0b00000000;

    }

}

//  --------------------------------------------------------------------------------------


// ------------------------------------------------------ //
// ---------------- CLASS IMPLEMENTATIONS --------------- //
// ------------------------------------------------------ //

shiftregdriver::shiftregdriver( uint16_t DIN, uint16_t SRCLK, uint16_t RCLK ) {

    _GPIO_PINOUT_INI.DIN    = DIN;      // SER data input
    _GPIO_PINOUT_INI.SRCLK  = SRCLK;    // SER clock
    _GPIO_PINOUT_INI.RCLK   = RCLK;     // Latch clock
    ini                     = true;     /* initiated */

}

shiftregdriver::shiftregdriver( uint16_t DIN, uint16_t SRCLK, uint16_t RCLK, uint16_t SRCLK_RPIN ) {

    _GPIO_PINOUT_INI.DIN            = DIN;          // SER data input
    _GPIO_PINOUT_INI.SRCLK          = SRCLK;        // SER clock
    _GPIO_PINOUT_INI.RCLK           = RCLK;         // Latch clock
    _GPIO_PINOUT_INI.SRCLK_RPIN     = SRCLK_RPIN;   // SER clock Reset pin
    ini                             = true;         /* initiated */
    rpin_set                        = true;         /* Reset Pin was used and set */

}

void shiftregdriver::begin( bool manual_ovr = 0 ) {

    if ( ini && !manual_ovr )
    {

        // shiftregister::begin | input_gpio | start ####****####
        sr_gpio_conf_input.intr_type    = GPIO_INTR_DISABLE;
        sr_gpio_conf_input.mode         = GPIO_MODE_OUTPUT;

        if ( rpin_set ) // check if rpin was set
        {
            sr_gpio_conf_input.pin_bit_mask = ( 1ULL << ( gpio_num_t ) _GPIO_PINOUT_INI.DIN ) | ( 1ULL << ( gpio_num_t ) _GPIO_PINOUT_INI.SRCLK_RPIN );
        } else
        {
            sr_gpio_conf_input.pin_bit_mask = ( 1ULL << ( gpio_num_t ) _GPIO_PINOUT_INI.DIN ); // | ( 1ULL << ( gpio_num_t ) _GPIO_PINOUT_INI.SRCLK_RPIN );
        }               // if exit

        sr_gpio_conf_input.pull_down_en = GPIO_PULLDOWN_DISABLE;
        sr_gpio_conf_input.pull_up_en   = GPIO_PULLUP_DISABLE;
        // shiftregister::begin | input_gpio | end   ####****####

        //  --------------------------------------------------------------------------------------

        // shiftregister::begin | clk_gpio | start   ####****####
        sr_gpio_conf_clk.intr_type      = GPIO_INTR_DISABLE;
        sr_gpio_conf_clk.mode           = GPIO_MODE_OUTPUT;
        sr_gpio_conf_clk.pin_bit_mask   = ( 1ULL << (gpio_num_t) _GPIO_PINOUT_INI.RCLK ) | ( 1ULL << ( gpio_num_t ) _GPIO_PINOUT_INI.SRCLK );
        sr_gpio_conf_clk.pull_down_en   = GPIO_PULLDOWN_DISABLE;
        sr_gpio_conf_clk.pull_up_en     = GPIO_PULLUP_DISABLE;
        // shiftregister::begin | clk_gpio | end     ####****####

        // initiate and set pins
        gpio_config( &sr_gpio_conf_input );     // initiate input
        gpio_config( &sr_gpio_conf_clk );       // initiate clk
        
        return;

    } else
    {
        
        if ( !ini && manual_ovr ) printf( "%sInitiate first before using the begin and override.\n", (char*)TAGSRPR );    // print if manual override was set but wasnt initialized
        if ( ini && manual_ovr ) printf( "%sManual Override was set.\n", (char*)TAGSRPR );                                // print if manual override was set and was initialized
        return;

    }

}

//  --------------------------------------------------------------------------------------

void shiftregdriver::write( uint8_t D_array ) {

    uint8_t i;

    for ( i = 0; i< 8; i++ )
    {

        gpio_set_level( ( gpio_num_t ) _GPIO_PINOUT_INI.DIN, !!( D_array & ( 1 << i ) ) );  // Just convert or make sure its true boolean -> !!( ... )
        /** Theres should be a small ns delay here. */
        gpio_set_level( ( gpio_num_t ) _GPIO_PINOUT_INI.SRCLK, HIGH );  // shift the bit
        gpio_set_level( ( gpio_num_t ) _GPIO_PINOUT_INI.SRCLK, LOW );   // Ready for next bit to shift

    }
    
    printf( "%sDone writing..\n", TAGSRPR );
    return;

}
/** Overload
 * 
 */

void shiftregdriver::write( uint8_t D_array, bool lsb = 1 ) {

    uint8_t i;

    if ( lsb )
    {

        for ( i = 0; i< 8; i++ )
        {

            gpio_set_level( ( gpio_num_t ) _GPIO_PINOUT_INI.DIN, !!( D_array & ( 1 << i ) ) );  // Just convert or make sure its true boolean -> !!( ... )
            /** Theres should be a small ns delay here. */
            gpio_set_level( ( gpio_num_t ) _GPIO_PINOUT_INI.SRCLK, HIGH );  // shift the bit
            gpio_set_level( ( gpio_num_t ) _GPIO_PINOUT_INI.SRCLK, LOW );   // Ready for next bit to shift

        }
        
        printf( "%sDone writing..\n", TAGSRPR );
        return;

    } else // print in msb
    {

        for ( i = 0; i< 8; i++ )
        {

            gpio_set_level( ( gpio_num_t ) _GPIO_PINOUT_INI.DIN, !!( D_array & ( 1 << ( 7 - i ) ) ) );  // Just convert or make sure its true boolean -> !!( ... )
            /** Theres should be a small ns delay here. */
            gpio_set_level( ( gpio_num_t ) _GPIO_PINOUT_INI.SRCLK, HIGH );  // shift the bit
            gpio_set_level( ( gpio_num_t ) _GPIO_PINOUT_INI.SRCLK, LOW );   // Ready for next bit to shift

        }

        printf( "%sDone writing..\n", TAGSRPR );
        return;

    }

}

//  --------------------------------------------------------------------------------------

void shiftregdriver::writel( uint8_t D_array ) {

    uint8_t i;

    gpio_set_level( ( gpio_num_t ) _GPIO_PINOUT_INI.RCLK, LOW );

    for ( i = 0; i< 8; i++ )
    {

        gpio_set_level( ( gpio_num_t ) _GPIO_PINOUT_INI.DIN, !!( D_array & ( 1 << i ) ) );  // Just convert or make sure its true boolean -> !!( ... )
        /** Theres should be a small ns delay here. */
        gpio_set_level( ( gpio_num_t ) _GPIO_PINOUT_INI.SRCLK, HIGH );  // shift the bit
        gpio_set_level( ( gpio_num_t ) _GPIO_PINOUT_INI.SRCLK, LOW );   // Ready for next bit to shift

    }
    
    gpio_set_level( ( gpio_num_t ) _GPIO_PINOUT_INI.RCLK, HIGH );
    printf( "%sDone writing, now latched\n", TAGSRPR );
    return;

}
/**
 * Overload
 */

void shiftregdriver::writel( uint8_t D_array, bool lsb = 1 ) {

    uint8_t i;

    gpio_set_level( ( gpio_num_t ) _GPIO_PINOUT_INI.RCLK, LOW );

    if ( lsb )
    {

        for ( i = 0; i< 8; i++ )
        {

            gpio_set_level( ( gpio_num_t ) _GPIO_PINOUT_INI.DIN, !!( D_array & ( 1 << i ) ) );  // Just convert or make sure its true boolean -> !!( ... )
            /** Theres should be a small ns delay here. */
            gpio_set_level( ( gpio_num_t ) _GPIO_PINOUT_INI.SRCLK, HIGH );  // shift the bit
            gpio_set_level( ( gpio_num_t ) _GPIO_PINOUT_INI.SRCLK, LOW );   // Ready for next bit to shift

        }
        
        gpio_set_level( ( gpio_num_t ) _GPIO_PINOUT_INI.RCLK, HIGH );
        printf( "%sDone writing, now latched\n", TAGSRPR );
        return;

    } else // print in msb
    {

        for ( i = 0; i< 8; i++ )
        {

            gpio_set_level( ( gpio_num_t ) _GPIO_PINOUT_INI.DIN, !!( D_array & ( 1 << ( 7 - i ) ) ) );  // Just convert or make sure its true boolean -> !!( ... )
            /** Theres should be a small ns delay here. */
            gpio_set_level( ( gpio_num_t ) _GPIO_PINOUT_INI.SRCLK, HIGH );  // shift the bit
            gpio_set_level( ( gpio_num_t ) _GPIO_PINOUT_INI.SRCLK, LOW );   // Ready for next bit to shift

        }
        gpio_set_level( ( gpio_num_t ) _GPIO_PINOUT_INI.RCLK, HIGH );
        printf( "%sDone writing, now latched\n", TAGSRPR );
        return;

    }

}

//  --------------------------------------------------------------------------------------

void shiftregdriver::printstr(const char* string, bool lsb = 1) {

    // check if string has no input
    if (string == nullptr || string[0] == '\0') 
    {
        return;
    }

    // dynamically allocate memory for the string
    size_t len = strlen(string);
    uint8_t* arrstr = new uint8_t[len]();  // Initialize array to 0

    // send the string as binary to the arrstr array
    for (size_t i = 0; i < len; i++) 
    {
        arrstr[i] = charto8bit(string[( len - 1 ) - i]);
    }

    // write to the shift register(s)
    if ( len > sseg_count )
    {
        printf( "%sChar is too long for the given shift registers...\n", TAGSRPR );

    } else
    {
        for ( size_t i = 0; i < len - 1; i++ ) // write all string except for last ( will be latched )
        {
            write( arrstr[i], lsb );
        }

        writel( arrstr[ len - 1], lsb ); // latch after
    }

    delete[] arrstr;  // Use delete[] for dynamic arrays
}

//  --------------------------------------------------------------------------------------

void shiftregdriver::ssegc( uint8_t count ) {

    sseg_count = count;
    return;

}

//  --------------------------------------------------------------------------------------

// ----------- CLEAR BITS IN SHIFT REGISTER(S) ---------- //
void shiftregdriver::clear() {

    uint8_t bitclear_c = sseg_count * 8;


    gpio_set_level( ( gpio_num_t ) _GPIO_PINOUT_INI.RCLK, LOW );
    for ( int i = 0; i < bitclear_c; i++ )
    {
        gpio_set_level( ( gpio_num_t ) _GPIO_PINOUT_INI.DIN, LOW );
        gpio_set_level( ( gpio_num_t ) _GPIO_PINOUT_INI.SRCLK, HIGH );
        gpio_set_level( ( gpio_num_t ) _GPIO_PINOUT_INI.SRCLK, LOW );
    }
    gpio_set_level( ( gpio_num_t ) _GPIO_PINOUT_INI.RCLK, HIGH );

    return;

}

//  --------------------------------------------------------------------------------------

void shiftregdriver::printstrf(const char* format, ...) {

    varg(format, arg...)
    varg = new arg[sizeof(format)]();

}

//  --------------------------------------------------------------------------------------