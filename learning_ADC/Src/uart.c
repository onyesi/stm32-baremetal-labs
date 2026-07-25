/*
 * uart.c
 *
 *  Created on: Jul 24, 2026
 *      Author: john
 */

#include "uart.h"      // Include UART function prototypes and STM32 register definitions

/* USART Clock Enable */
#define USART2EN       (1U << 17)      // Enable clock for USART2

/* UART Configuration */
#define DBG_UART_BAUDRATE 115200       // Desired UART baud rate
#define SYS_FREQ       16000000        // System clock = 16 MHz
#define APB1_CLK       SYS_FREQ        // APB1 bus clock

/* USART Status Register (SR) Bits */
#define TXE            (1U << 7)       // Transmit data register empty
#define RXNE           (1U << 5)       // Receive data register not empty
#define TC             (1U << 6)       // Transmission complete
#define ORE            (1U << 3)       // Overrun error

/* USART Control Register 1 (CR1) Bits */
#define UE             (1U << 13)      // USART enable
#define M              (1U << 12)      // Word length
#define TE             (1U << 3)       // Transmitter enable
#define RE             (1U << 2)       // Receiver enable
#define PCE            (1U << 10)      // Parity control enable
#define PS             (1U << 9)       // Parity selection

/*----------------------------------------------------------
 * Function : USART_Init
 * Purpose  : Configure USART2 peripheral
 *---------------------------------------------------------*/
void USART_Init(void)
{
    /* Enable clock access to USART2 */
    RCC->APB1ENR |= USART2EN;

    /* Configure baud rate */
    USART2->BRR = (APB1_CLK / DBG_UART_BAUDRATE);

    /* Configure 8-bit word length */
    USART2->CR1 &= ~M;

    /* Disable parity */
    USART2->CR1 &= ~PCE;

    /* Enable transmitter */
    USART2->CR1 |= TE;

    /* Enable receiver */
    USART2->CR1 |= RE;

    /* Enable USART2 peripheral */
    USART2->CR1 |= UE;
}

/*----------------------------------------------------------
 * Function : Transmit_data
 * Purpose  : Transmit one byte through USART2
 *---------------------------------------------------------*/
void Transmit_data(uint8_t data)
{
    /* Wait until transmit data register is empty */
    while (!(USART2->SR & TXE))
    {
    }

    /* Load data into transmit register */
    USART2->DR = data;

    /* Wait until transmission is complete */
    while (!(USART2->SR & TC))
    {
    }
}

/*----------------------------------------------------------
 * Function : Receive_data
 * Purpose  : Receive one byte from USART2
 *---------------------------------------------------------*/
uint8_t Receive_data(void)
{
    /* Wait until a byte has been received */
    while (!(USART2->SR & RXNE))
    {
    }

    /* Return received byte */
    return USART2->DR;
}

/*----------------------------------------------------------
 * Function : __io_putchar
 * Purpose  : Redirect printf() output to USART2
 *---------------------------------------------------------*/
int __io_putchar(int ch)
{
    Transmit_data((uint8_t)ch);

    return ch;
}
