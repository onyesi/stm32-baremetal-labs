# stm32-baremetal-labs


## Overview

This repository documents the development of an autonomous weather monitoring system using the **STM32 NUCLEO-F446RE** development board through bare-metal programming.

The objective of this project is to strengthen my practical embedded software development skills by implementing STM32 peripherals directly from the Reference Manual using CMSIS register.

Instead of learning GPIO, UART, ADC and other peripherals as isolated topics, I chose to build a complete embedded application and allow its system requirements to determine which peripherals needed to be implemented.

As the project evolves, additional peripherals, sensors and software modules will be introduced to satisfy new functional requirements.

<img width="3024" height="4032" alt="LDR" src="https://github.com/user-attachments/assets/5a43b371-b065-4411-bbbc-19e58a953ffc" />


# Project Goal

The long-term objective is to develop an autonomous weather monitoring system capable of:

- Measuring environmental conditions
- Processing sensor data
- Displaying useful information
- Logging measurements
- Communicating with external devices
- Operating autonomously with minimal user intervention

Each development milestone adds new functionality while expanding the embedded software architecture.



# Development Journey

## Stage 1 — Establishing the Hardware Foundation

Every embedded systems project usually begins with GPIO, and this project was no different.

The first task was to interface an external LED with the STM32. Besides learning how to configure GPIO registers directly from the STM32 Reference Manual, the LED also provided a quick method of confirming that the breadboard was correctly powered and that the microcontroller could successfully control external hardware.

This stage introduced fundamental concepts including:

- Peripheral clock configuration
- GPIO modes
- Output registers
- Bit manipulation
- Register-level programming using CMSIS



## Stage 2 — Introducing the First Sensor

The first sensor selected for the weather monitoring system was an **LDR (Light Dependent Resistor)** to measure ambient light intensity.

Because the LDR produces an analogue voltage, implementing it required learning the STM32 **Analog-to-Digital Converter (ADC)** peripheral.

This stage involved much more than configuring ADC registers. It also required understanding how the LDR and resistor formed a voltage divider, allowing changes in light intensity to be converted into analogue voltages that the STM32 could measure.

At this stage the project could successfully acquire analogue sensor data.



## Stage 3 — Improving Debugging with UART

While testing the ADC, it quickly became apparent that simply turning an LED on and off was not sufficient for debugging.

Although the LED should indicated whether a threshold had been exceeded, it provided no information about the actual ADC conversion values which could have helped me set a reasonable threshold.

To improve visibility into the system, a UART driver was implemented using USART2.

The standard C `printf()` function was redirected to UART, allowing sensor readings to be transmitted directly to a serial terminal.

This significantly simplified debugging by making it possible to observe ADC conversion values in real time while testing different lighting conditions.

The GPIO knowledge acquired during the first stage was reused when configuring the alternate-function pins required by the UART peripheral.


 Current Stage

The first stage of the project establishes the basic software infrastructure required for future development.

Currently implemented:

- GPIO Driver
- USART2 Driver
- ADC1 Driver

Current functionality:

- Reads ambient light using an LDR connected to ADC1 Channel 7.
- Continuously converts the analogue voltage into a digital value.
- Sends ADC readings to a serial terminal using USART2.
- Redirects the C `printf()` function to UART for debugging.
- Turns an external LED ON or OFF depending on the measured light level.



## What I learned during this stage

This stage required me to understand and implement:

- GPIO configuration
- Alternate Function configuration
- UART communication
- Redirecting `printf()` to USART
- ADC configuration
- Continuous conversion mode
- Polling for End Of Conversion
- Register-level programming using CMSIS
- Software modularisation

While developing this project, I also encountered practical debugging challenges such as incorrect ADC channel selection, floating analogue inputs and GPIO pin conflicts. These issues were resolved by referring to the STM32 Reference Manual and by restructuring the software into separate GPIO, UART and ADC drivers.
