/*
 * adc.h
 *
 *  Created on: 25 Jul 2026
 *      Author: ABIAGAM
 */

#ifndef ADC_H_
#define ADC_H_
#include <stdint.h>
#include "stm32f4xx.h"

void ADC_INIT(void);
uint16_t ADC_Read(void);



#endif /* ADC_H_ */
