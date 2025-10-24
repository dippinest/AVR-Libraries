
#ifndef UART0_ASYNC_CONFIGURATION_H_
#define UART0_ASYNC_CONFIGURATION_H_



// если вы хотите активировать асинхронный приём данных по UART0,
// раскомментируйте этот дефайн (иначе закомментируйте его)
// -------------------------------------------------------------------------------
// if you want to activate asynchronous data reception via UART0,
// uncomment this define (otherwise comment it out)

#define UART0_ASYNC_USE_RX



// если вы хотите активировать асинхронную передачу данных по UART0,
// раскомментируйте этот дефайн (иначе закомментируйте его)
// -------------------------------------------------------------------------------
// if you want to activate asynchronous data transfer via UART0,
// uncomment this define (otherwise comment it out)

#define UART0_ASYNC_USE_TX

#endif
