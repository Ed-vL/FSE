#ifndef _UART_
#define _UART_
extern int uart0_filestream;

void openUart();
void closeUart();
float getTempUart(char code, int size,int retries);

#endif