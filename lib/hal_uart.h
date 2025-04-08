#ifndef _HAL_UART_H_
#define _HAL_UART_H_

#include "hal_config.h"

#define UART_BAUD               9600
#define UART_RX_BUFFER_SIZE     32
#define UART_DATA_BITS          8       //5, 6, 7, 8, 9
#define UART_PARITY             0       //0=NONE, 1=ODD, 2=EVEN
#define UART_STOP_BITS          1       //1, 2
#define UART_RX_INTERRUPT       1       //0=Disable, 1=Enable

void HAL_UART_Init(void);
void HAL_UART_Process(void);
__attribute__((weak)) void HAL_UART_CommandHandler(const char* cmd);

#endif /*_HAL_UART_H_*/
