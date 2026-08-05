
#ifndef UART_ASYNC_CONFIGURATION_H_
#define UART_ASYNC_CONFIGURATION_H_



// если вы хотите активировать асинхронный приём данных по UART,
// раскомментируйте этот дефайн (иначе закомментируйте его)
// -------------------------------------------------------------------------------
// if you want to activate asynchronous data reception via UART,
// uncomment this define (otherwise comment it out)

#define UART_ASYNC_USE_RX



// если вы хотите активировать асинхронную передачу данных по UART,
// раскомментируйте этот дефайн (иначе закомментируйте его)
// -------------------------------------------------------------------------------
// if you want to activate asynchronous data transfer via UART,
// uncomment this define (otherwise comment it out)

#define UART_ASYNC_USE_TX

#endif
