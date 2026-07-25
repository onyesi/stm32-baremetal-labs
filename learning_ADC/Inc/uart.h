/*
 * uart.h
 *
 *  Created on: Jul 24, 2026
 *      Author: john
 */

#ifndef UART_H_
#define UART_H_
#include <stdint.h>
#include "stm32f4xx.h"
void USART_Init(void);
void Transmit_data(uint8_t Data);
uint8_t  Receive_data(void);
int __io_putchar(int ch);



#endif /* UART_H_ */
