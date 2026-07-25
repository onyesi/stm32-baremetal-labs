/*
 * GPIO.c
 *
 *  Created on: 25 Jul 2026
 *      Author: ABIAGAM
 */

#include "GPIO.h"          // Include function prototypes and STM32 register definitions

/* GPIO Clock Enable */
#define GPIOAEN (1U<<0)     // Bit 0 of RCC->AHB1ENR enables clock for GPIO Port A

/* LED Definitions */
#define PIN0 (1U<<0)        // Pin 0 mask
#define LED_PIN PIN0        // LED is connected to PA0

/*----------------------------------------------------------
 * Function: GPIO_INIT
 * Purpose : Configure all GPIO pins used in this project
 *---------------------------------------------------------*/
void GPIO_INIT(void)
{
    /* Enable clock access to GPIOA */
    RCC->AHB1ENR |= GPIOAEN;

    /*--------------- PA0 : LED Output ----------------*/

    GPIOA->MODER |= (1U << 0);      // Set MODER0 bit 0 = 1
    GPIOA->MODER &= ~(1U << 1);     // Clear MODER0 bit 1 = 0
                                    // PA0 Mode = 01 (General Purpose Output)

    /*--------------- PA2 : USART2 TX ----------------*/

    GPIOA->MODER &= ~(1U << 4);     // Clear MODER2 bit 0
    GPIOA->MODER |=  (1U << 5);     // Set MODER2 bit 1
                                    // PA2 Mode = 10 (Alternate Function)

    /*--------------- PA3 : USART2 RX ----------------*/

    GPIOA->MODER &= ~(1U << 6);     // Clear MODER3 bit 0
    GPIOA->MODER |=  (1U << 7);     // Set MODER3 bit 1
                                    // PA3 Mode = 10 (Alternate Function)

    /*--------------- PA2 Alternate Function ---------*/

    GPIOA->AFR[0] |=  (1U << 8);    // AFRL2 bit 0 = 1
    GPIOA->AFR[0] |=  (1U << 9);    // AFRL2 bit 1 = 1
    GPIOA->AFR[0] |=  (1U <<10);    // AFRL2 bit 2 = 1
    GPIOA->AFR[0] &= ~(1U <<11);    // AFRL2 bit 3 = 0
                                    // AF = 0111 (AF7 = USART2_TX)

    /*--------------- PA3 Alternate Function ---------*/

    GPIOA->AFR[0] |=  (1U <<12);    // AFRL3 bit 0 = 1
    GPIOA->AFR[0] |=  (1U <<13);    // AFRL3 bit 1 = 1
    GPIOA->AFR[0] |=  (1U <<14);    // AFRL3 bit 2 = 1
    GPIOA->AFR[0] &= ~(1U <<15);    // AFRL3 bit 3 = 0
                                    // AF = 0111 (AF7 = USART2_RX)

    /*--------------- PA7 : ADC1_IN7 -----------------*/

    GPIOA->MODER |= (1U <<14);      // Set MODER7 bit 0
    GPIOA->MODER |= (1U <<15);      // Set MODER7 bit 1
                                    // PA7 Mode = 11 (Analog Mode)
}

/*----------------------------------------------------------
 * Function: led_On
 * Purpose : Turn ON the LED connected to PA0
 *---------------------------------------------------------*/
void led_On(void)
{
    GPIOA->ODR |= LED_PIN;          // Write logic HIGH to PA0
}

/*----------------------------------------------------------
 * Function: led_Off
 * Purpose : Turn OFF the LED connected to PA0
 *---------------------------------------------------------*/
void led_Off(void)
{
    GPIOA->ODR &= ~LED_PIN;         // Write logic LOW to PA0
}
