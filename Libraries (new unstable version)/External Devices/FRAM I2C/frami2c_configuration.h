
#ifndef FRAMI2C_CONFIGURATION_H_
#define FRAMI2C_CONFIGURATION_H_


// если вы хотите работать с устройством посредством программного I2C,
// раскомментируйте этот дефайн (иначе закомментируйте его)
// -------------------------------------------------------------------------------
// if you want to work with the device via software I2C,
// uncomment this define (otherwise comment it out)

#define FRAMI2C_USE_SOFTI2C





#ifdef FRAMI2C_USE_SOFTI2C

#warning "COMPILER MESSAGE: Library "frami2c.h" use software I2C!"

#else

#warning "COMPILER MESSAGE: Library "frami2c.h" use hardware I2C!"

#endif



#endif


