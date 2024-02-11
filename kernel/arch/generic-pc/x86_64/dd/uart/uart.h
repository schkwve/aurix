#ifndef UART_H
#define UART_H

#define COM1 0x3F8

void uart_init();
void uart_write(char *str);

#endif /* UART_H */
