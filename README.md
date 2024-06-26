# UART_and_LIN_S32K312

This repository contains code to implement UART and LIN communication protocols for the NXP S32K312 microcontroller using polling. The code includes configurations for UART transmission and reception, STM timer setup, and LED control based on UART communication status.

## Features

- **UART Communication:**
  - Polling-based UART transmission and reception.
  - Error handling and status indication using LEDs.

- **STM Timer:**
  - Configures STM for periodic interrupts.
  - Manages global counter and LED toggling.

- **LED Control:**
  - Uses LEDs to indicate UART communication status and errors.

## Code Overview

### Main Functions

- **`STM_Init()`**: Initializes the STM timer with a 1 ms period and sets up the interrupt handler.
- **`Stm0_Ch0_Callback(uint8 channel)`**: Callback function for STM channel 0 interrupt, toggles the LED and manages the global counter.
- **`LED_Init()`**: Configures the GPIO pins for LED control.
- **`LPUART_Init()`**: Initializes the UART module, sets up TX and RX buffers.
- **`UART_Error_Handler(Lpuart_Uart_Ip_StatusType Status)`**: Handles UART errors and controls LEDs based on the error type.
- **`delayMS(struct Wait *delay)`**: Implements a delay function using the global counter.

### Usage Example

The main function initializes all modules, configures the STM timer, LEDs, and UART, and enters an infinite loop where it toggles an LED based on UART transmission status.

### Code Snippet

```c
#include "Mcal.h"
#include "S32K312.h"
#include "Clock_Ip.h"
#include "Siul2_Port_Ip.h"
#include "OsIf.h"
#include "IntCtrl_Ip.h"
#include "Stm_Ip.h"
#include "Lpuart_Uart_Ip.h"
#include "Siul2_Dio_Ip.h"
#include <string.h>
#include <stdio.h>

// Macro definitions
#define LPUART_UART_INSTANCE    0
#define BUFFER_SIZE            100
#define STM0_INST              0
#define STM0_CH0               0
#define STM_PERIOD             1000

// Global variables
uint8_t txBuffer[BUFFER_SIZE];
uint8_t rxBuffer[BUFFER_SIZE];
volatile uint32_t rxBufferLength = 0;
uint16_t Global_Counter = 0;
volatile uint8 toggleLed = 0U;

// Function prototypes
void STM_Init(void);
void Stm0_Ch0_Callback(uint8 channel);
void LED_Init(void);
void LPUART_Init(void);
void UART_Error_Handler(Lpuart_Uart_Ip_StatusType Status);
int delayMS(struct Wait *delay);

// Main function
int main(void) {
    Clock_Ip_Init(&Clock_Ip_aClockConfig[0]);
    Clock_Ip_EnableModuleClock(SIUL2_CLK);

    IntCtrl_Ip_Init(&IntCtrlConfig_0);

    Siul2_Port_Ip_Init(NUM_OF_CONFIGURED_PINS0, g_pin_mux_InitConfigArr0);

    OsIf_Init(NULL);

    STM_Init();
    LED_Init();
    LPUART_Init();

    while (1) {
        Lpuart_Uart_Ip_StatusType Uart_status;
        if (toggleLed == 1) {
            Siul2_Dio_Ip_WritePin(LED_GREEN_PORT, LED_GREEN_PIN, 1); // Turn on LED_GREEN_PIN

            Uart_status = Lpuart_Uart_Ip_SyncSend(LPUART_UART_INSTANCE, (uint8_t *)"LED On\n", 7, 500000);
            UART_Error_Handler(Uart_status);

        } else if (toggleLed == 2) {
            Siul2_Dio_Ip_WritePin(LED_GREEN_PORT, LED_GREEN_PIN, 0); // Turn off LED_GREEN_PIN

            Uart_status = Lpuart_Uart_Ip_SyncSend(LPUART_UART_INSTANCE, (uint8_t *)"LED Off\n", 8, 500000);
            UART_Error_Handler(Uart_status);
        }
    }
}
