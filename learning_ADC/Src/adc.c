/*
 * adc.c
 *
 *  Created on: 25 Jul 2026
 *      Author: ABIAGAM
 */

#include "adc.h"            // Include ADC function prototypes and STM32 register definitions

/* ADC Status Register Definitions */
#define EOC (1U << 4)        // End Of Conversion flag (ADC_SR bit 4)

/*----------------------------------------------------------
 * Function: ADC_INIT
 * Purpose : Configure ADC1 for continuous conversion
 *           on channel 7 (PA7)
 *---------------------------------------------------------*/
void ADC_INIT(void)
{
    /* Enable clock access to ADC1 */
    RCC->APB2ENR |= (1U << 8);

    /*--------------- ADC Resolution ----------------*/

    ADC1->CR1 &= ~(1U << 24);    // Clear RES bit 0
    ADC1->CR1 &= ~(1U << 25);    // Clear RES bit 1
                                 // Resolution = 00 (12-bit)

    /*--------------- ADC Configuration -------------*/

    ADC1->CR2 |= (1U << 1);      // Enable Continuous Conversion Mode

    ADC1->CR2 &= ~(1U << 11);    // Right-align conversion result

    // ADC1->CR2 |= EOC;         // (Not used) EOC selection

    /*--------------- Status Flags ------------------*/

    // ADC1->SR |= (1U << 1);    // STRT flag (not required)
    // ADC1->SR |= EOC;          // EOC flag (hardware sets this automatically)

    /*--------------- Sample Time -------------------*/

    /* Configure sample time for Channel 7 */

    ADC1->SMPR2 |= (1U << 21);   // SMP7 bit 0 = 1
    ADC1->SMPR2 &= ~(1U << 22);  // SMP7 bit 1 = 0
    ADC1->SMPR2 &= ~(1U << 23);  // SMP7 bit 2 = 0
                                 // Sample Time = 001

    /*--------------- Conversion Sequence -----------*/

    /* Select Channel 7 as the first conversion */

    ADC1->SQR3 |= (1U << 0);     // SQ1 bit 0 = 1
    ADC1->SQR3 |= (1U << 1);     // SQ1 bit 1 = 1
    ADC1->SQR3 |= (1U << 2);     // SQ1 bit 2 = 1
    ADC1->SQR3 &= ~(1U << 3);    // SQ1 bit 3 = 0
    ADC1->SQR3 &= ~(1U << 4);    // SQ1 bit 4 = 0
                                 // SQ1 = 00111 (Channel 7)

    /*--------------- Enable ADC --------------------*/

    ADC1->CR2 |= (1U << 0);      // ADON = 1 (Enable ADC)

    /*--------------- Start Conversion --------------*/

    ADC1->CR2 |= (1U << 30);     // SWSTART = 1 (Start software conversion)
}

/*----------------------------------------------------------
 * Function: ADC_Read
 * Purpose : Wait for conversion to complete and
 *           return the ADC conversion result
 *---------------------------------------------------------*/
uint16_t ADC_Read(void)
{
    /* Wait until End Of Conversion flag becomes set */
    while (!(ADC1->SR & EOC))
    {
    }

    /* Read conversion result
       Reading the Data Register clears the EOC flag */
    return (uint16_t)ADC1->DR;
}
