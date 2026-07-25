#include <stdio.h>
#include   "stm32f4xx.h"
#include "GPIO.h"
#include "uart.h"
#include "adc.h"

#define Threshold 300


uint32_t sensorValue = 0;

int main()
{
	GPIO_INIT();
	USART_Init();
	ADC_INIT();




	while(1){




		sensorValue = ADC_Read();

		printf("Sensor = %lu\r\n", sensorValue);

		if(sensorValue > Threshold){
			led_On();
		}

		else
		{
			led_Off();

		}

	}




}
