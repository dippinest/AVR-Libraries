
#ifndef NTC_THERMOMETER_CONFIGURATION_H_
#define NTC_THERMOMETER_CONFIGURATION_H_

#include <math.h>
#include <stdint.h>

// (I calculated the coefficients for the NTC thermistor MF52 NTC-MF52AT 100 kOhm)

// coefficient A
#define A_COEF       0.0006660824105f

// coefficient B
#define B_COEF       0.0002239282041f

// coefficient C
#define C_COEF       0.0000000719951882f

// serial resistor resistance in ohms (measured with a multimeter)
#define SERIAL_R     98600

// +Vcc voltage
#define U_GEN        4.81f

// ADC reference voltage
#define U_REF        4.81f

// ADC max value
#define ADC_MAX_VAL  1023 // max value 10-bit ADC

#endif