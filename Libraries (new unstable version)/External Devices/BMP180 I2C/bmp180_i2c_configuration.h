
#ifndef BMP180_I2C_CONFIGURATION_H_
#define BMP180_I2C_CONFIGURATION_H_


// если вы хотите работать с устройством посредством программного I2C,
// раскомментируйте этот дефайн (иначе закомментируйте его)
// -------------------------------------------------------------------------------
// if you want to work with the device via software I2C,
// uncomment this define (otherwise comment it out)

#define BMP180_I2C_USE_SOFTI2C





#ifdef BMP180_I2C_USE_SOFTI2C

#warning "COMPILER MESSAGE: Library "bmp180_i2c.h" use software SPI!"

#else

#warning "COMPILER MESSAGE: Library "bmp180_i2c.h" use hardware SPI!"

#endif



#endif




