#include <stdio.h>          // Provides printf()
#include "stm32f4xx.h"      // CMSIS device definitions for STM32F446RE
#include "GPIO.h"           // GPIO driver interface
#include "uart.h"           // UART driver interface
#include "adc.h"            // ADC driver interface

// ADC threshold used to control the external LED.
// If the measured ADC value exceeds this threshold,
// the LED is turned ON.
#define Threshold 300

// Stores the latest ADC conversion result.
uint32_t sensorValue = 0;

int main(void)
{
    /*----------------------------------------------------------
     * Peripheral Initialization
     *----------------------------------------------------------
     * Initialise all peripherals required by the application.
     * The order is important because each peripheral depends on
     * its hardware resources being configured correctly.
     */
    GPIO_INIT();     // Configure GPIO pins
    USART_Init();    // Initialise USART2 for serial communication
    ADC_INIT();      // Configure ADC1 for continuous conversion

    /*----------------------------------------------------------
     * Main Application Loop
     *----------------------------------------------------------
     * Continuously:
     *  1. Read the analogue sensor.
     *  2. Send the reading to the serial terminal.
     *  3. Compare the reading with the threshold.
     *  4. Turn the LED ON or OFF accordingly.
     */
    while (1)
    {
        // Read the latest ADC conversion result.
        sensorValue = ADC_Read();

        // Print the sensor value through USART2.

        printf("Sensor = %lu\r\n", sensorValue);

        // Compare the sensor value against the threshold.
        if (sensorValue > Threshold)
        {
            // Light level exceeds the threshold.
            // Turn the external LED ON.
            led_On();
        }
        else
        {
            // Light level is below the threshold.
            // Turn the external LED OFF.
            led_Off();
        }
    }
}
