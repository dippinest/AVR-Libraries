
#ifndef HD44780_I2C_CONFIGURATION_H_
#define HD44780_I2C_CONFIGURATION_H_


// если вы хотите работать с устройством посредством программного I2C,
// раскомментируйте этот дефайн (иначе закомментируйте его)
// -------------------------------------------------------------------------------
// if you want to work with the device via software I2C,
// uncomment this define (otherwise comment it out)

#define HD44780_I2C_USE_SOFTI2C





#ifdef HD44780_I2C_USE_SOFTI2C

#warning "COMPILER MESSAGE: Library "hd44780_i2c.h" use software I2C!"

#else

#warning "COMPILER MESSAGE: Library "hd44780_i2c.h" use hardware I2C!"

#endif



#endif


