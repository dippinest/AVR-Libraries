
#ifndef MAX7219_SYMBOLS_H_
#define MAX7219_SYMBOLS_H_

// macros of special character codes
#define MAX7219_EMPTY        0b00000000
#define MAX7219_SPACE        0b00000000
#define MAX7219_POINT        0b10000000
#define MAX7219_MINUS        0b00000001
#define MAX7219_DASH         0b00000001
#define MAX7219_DEGREE       0b01100011
#define MAX7219_OVERLINE     0b01000000
#define MAX7219_UNDERSCORE   0b00001000

// macros of digit codes
#define MAX7219_0            0b01111110
#define MAX7219_1            0b00110000
#define MAX7219_2            0b01101101
#define MAX7219_3            0b01111001
#define MAX7219_4            0b00110011
#define MAX7219_5            0b01011011
#define MAX7219_6            0b01011111
#define MAX7219_7            0b01110000
#define MAX7219_8            0b01111111
#define MAX7219_9            0b01111011

// macros of codes of some Latin letters
#define MAX7219_A            0b01110111
#define MAX7219_b            0b00011111
#define MAX7219_C            0b01001110
#define MAX7219_c            0b00001101
#define MAX7219_d            0b00111101
#define MAX7219_E            0b01001111
#define MAX7219_F            0b01000111
#define MAX7219_G            0b01011111
#define MAX7219_g            0b01111011
#define MAX7219_H            0b00110111
#define MAX7219_h            0b00010111
#define MAX7219_I            0b00110000
#define MAX7219_i            0b00010000
#define MAX7219_J            0b00111000
#define MAX7219_j            0b00011000
#define MAX7219_L            0b00001110
#define MAX7219_l            0b00000110
#define MAX7219_n            0b00010101
#define MAX7219_O            0b01111110
#define MAX7219_o            0b00011101
#define MAX7219_P            0b01100111
#define MAX7219_q            0b01110011
#define MAX7219_r            0b00000101
#define MAX7219_S            0b01011011
#define MAX7219_t            0b00001111
#define MAX7219_U            0b00111110
#define MAX7219_v            0b00011100
#define MAX7219_y            0b00111011
#define MAX7219_Z            0b01001001


// macro for setting a dot in a character
#define MAX7219_CHAR_SIGN_WITH_POINT(MAX7219_CHAR)    (MAX7219_CHAR | 0b10000000)

// macro for resetting a dot in a character
#define MAX7219_CHAR_SIGN_WITHOUT_POINT(MAX7219_CHAR) (MAX7219_CHAR & 0b01111111)

#endif


