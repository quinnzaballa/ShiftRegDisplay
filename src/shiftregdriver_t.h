/** Reference ( 7-seg display )
 *       a
 *       _
 *   f  | |  b
 *       - g
 *   e  | |  c
 *       _
 *       d
 */

/** @cond */
typedef enum {
    /* Number | start */
//  **************************************************************************************
    //              abcdefgh | h is dp in schematics
    NUM_8_LSB_0 = 0b11111100,           // Display number 0 in 7seg.
    NUM_8_LSB_1 = 0b01100000,           // Display number 1 in 7seg.
    NUM_8_LSB_2 = 0b11011010,           // Display number 2 in 7seg.
    NUM_8_LSB_3 = 0b11110010,           // Display number 3 in 7seg.
    //              abcdefgh | h is dp in schematics
    NUM_8_LSB_4 = 0b01100110,           // Display number 4 in 7seg.
    NUM_8_LSB_5 = 0b10110110,           // Display number 5 in 7seg.
    NUM_8_LSB_6 = 0b10111110,           // Display number 6 in 7seg.
    NUM_8_LSB_7 = 0b11100000,           // Display number 7 in 7seg.
    //              abcdefgh | h is dp in schematics
    NUM_8_LSB_8 = 0b11111110,           // Display number 8 in 7seg.
    NUM_8_LSB_9 = 0b11110110,           // Display number 9 in 7seg.
    NUM_8_LSB_MAX
//  **************************************************************************************
    /* Number | end */
} shiftreg_num_8bit_lsb_t;
/** @endcond */

//  --------------------------------------------------------------------------------------

/** Reference ( 7-seg display )
 *       a
 *       _
 *   f  | |  b
 *       - g
 *   e  | |  c
 *       _
 *       d
 */

/** @cond */
typedef enum {
    /* Alphabet ( limited ) | start */
//  **************************************************************************************
    //              abcdefgh | h is dp in schematics
    APB_8_LSB_A = 0b11101110,
    APB_8_LSB_b = 0b00111110,
    APB_8_LSB_C = 0b10011100,
    APB_8_LSB_d = 0b01111010,
    //              abcdefgh | h is dp in schematics
    APB_8_LSB_E = 0b10011110,
    APB_8_LSB_F = 0b10001110,
    APB_8_LSB_g = 0b11110110,   // small G /* verified */
    APB_8_LSB_G = 0b10111100,
    //              abcdefgh | h is dp in schematics
    APB_8_LSB_h = 0b00101110,   // small H
    APB_8_LSB_H = 0b01101110,
    APB_8_LSB_i = 0b10100000,
    APB_8_LSB_I = 0b01100000,
    //              abcdefgh | h is dp in schematics
    APB_8_LSB_j = 0b10110000,   // small J
    APB_8_LSB_J = 0b01110000,
    APB_8_LSB_k = 0b01100010,   // no way i can literally do it in 7sesg xD
    APB_8_LSB_L = 0b00011100,   /* verified */
    //              abcdefgh | h is dp in schematics
    APB_8_LSB_n = 0b00101010,
    APB_8_LSB_o = 0b00111010,   // small O
    APB_8_LSB_O = 0b11111100,
    APB_8_LSB_P = 0b11001110,
    //              abcdefgh | h is dp in schematics
    APB_8_LSB_q = 0b11100110,
    APB_8_LSB_r = 0b11001100,
    APB_8_LSB_S = 0b10110110,
    APB_8_LSB_t = 0b00011110,
    //              abcdefgh | h is dp in schematics
    APB_8_LSB_u = 0b00111000, // small U
    APB_8_LSB_U = 0b01111100,
    APB_8_LSB_X = 0b01101110,
    APB_8_LSB_y = 0b01110110,
    APB_8_LSB_MAX
//  **************************************************************************************
    /* Alphabet ( limited ) | end */

    /* alphabets that cant be recognized as alphabet */
    // APB_8_LSB_Z = 0b01110110  impossible to print
    // APB_8_LSB_W = 0b01111100, impossible to print
    // APB_8_LSB_v = 0b01111100, impossible to print
    // APB_8_LSB_m = 0b00011100, impossible to print

} shiftreg_apb_8bit_lsb_t;
/** @endcond */

//  --------------------------------------------------------------------------------------

