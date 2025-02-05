
#ifndef MAX7219_SYMBOLS_H_
#define MAX7219_SYMBOLS_H_

// macros of special character codes
#define MAX7219_EMPTY_SYMB        0b00000000
#define MAX7219_SPACE_SYMB        0b00000000
#define MAX7219_POINT_SYMB        0b10000000
#define MAX7219_MINUS_SYMB        0b00000001
#define MAX7219_DASH_SYMB         0b00000001
#define MAX7219_DEGREE_SYMB       0b01100011
#define MAX7219_OVERLINE_SYMB     0b01000000
#define MAX7219_UNDERSCORE_SYMB   0b00001000

// macros of digit codes
#define MAX7219_0_SYMB            0b01111110
#define MAX7219_1_SYMB            0b00110000
#define MAX7219_2_SYMB            0b01101101
#define MAX7219_3_SYMB            0b01111001
#define MAX7219_4_SYMB            0b00110011
#define MAX7219_5_SYMB            0b01011011
#define MAX7219_6_SYMB            0b01011111
#define MAX7219_7_SYMB            0b01110000
#define MAX7219_8_SYMB           0b01111111
#define MAX7219_9_SYMB            0b01111011

// macros of codes of some Latin letters
#define MAX7219_A_SYMB            0b01110111
#define MAX7219_b_SYMB            0b00011111
#define MAX7219_C_SYMB            0b01001110
#define MAX7219_c_SYMB            0b00001101
#define MAX7219_d_SYMB            0b00111101
#define MAX7219_E_SYMB            0b01001111
#define MAX7219_F_SYMB            0b01000111
#define MAX7219_G_SYMB            0b01011111
#define MAX7219_g_SYMB            0b01111011
#define MAX7219_H_SYMB            0b00110111
#define MAX7219_h_SYMB            0b00010111
#define MAX7219_I_SYMB            0b00110000
#define MAX7219_i_SYMB            0b00010000
#define MAX7219_J_SYMB            0b00111000
#define MAX7219_j_SYMB            0b00011000
#define MAX7219_L_SYMB            0b00001110
#define MAX7219_l_SYMB            0b00000110
#define MAX7219_n_SYMB            0b00010101
#define MAX7219_O_SYMB            0b01111110
#define MAX7219_o_SYMB            0b00011101
#define MAX7219_P_SYMB            0b01100111
#define MAX7219_q_SYMB            0b01110011
#define MAX7219_r_SYMB            0b00000101
#define MAX7219_S_SYMB            0b01011011
#define MAX7219_t_SYMB            0b00001111
#define MAX7219_U_SYMB            0b00111110
#define MAX7219_v_SYMB            0b00011100
#define MAX7219_y_SYMB            0b00111011
#define MAX7219_Z_SYMB            0b01001001


// macro for setting a dot in a character
#define MAX7219_CHAR_SIGN_WITH_POINT(MAX7219_CHAR)    (MAX7219_CHAR | 0b10000000)

// macro for resetting a dot in a character
#define MAX7219_CHAR_SIGN_WITHOUT_POINT(MAX7219_CHAR) (MAX7219_CHAR & 0b01111111)

#endif


