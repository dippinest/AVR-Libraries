
#ifndef ENCODER_CONFIGURATION_H_
#define ENCODER_CONFIGURATION_H_


// если вы хотите работать с несколькими энкодерами, раскомментируйте
// этот дефайн (иначе закомментируйте его)
// -------------------------------------------------------------------------------
// if you want to work with multiple encoders, uncomment this define
// (otherwise comment it out)

//#define ENCODER_USE_MULTIPLE_DEVICES



#ifndef ENCODER_USE_MULTIPLE_DEVICES

// определения GPIO для первого входа энкодера
// -------------------------------------------------------------------------------
// GPIO definitions for the first encoder input

#define ENCODER_INPUT0_DDR   DDRA
#define ENCODER_INPUT0_PINX  PINA
#define ENCODER_INPUT0_PIN      0


// определения GPIO для второго входа энкодера
// -------------------------------------------------------------------------------
// GPIO definitions for the second encoder input

#define ENCODER_INPUT1_DDR   DDRA
#define ENCODER_INPUT1_PINX  PINA
#define ENCODER_INPUT1_PIN      1

#endif


#endif


