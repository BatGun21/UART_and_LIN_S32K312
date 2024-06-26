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

/* Macro definitions */
#define LPUART_UART_INSTANCE    0
#define BUFFER_SIZE            100
#define STM0_INST              0
#define STM0_CH0               0
#define STM_PERIOD             1000

/* Structs */
struct Wait {
	int currentTime;
	int delayTime ;
	int activeFlag;
};

/* Welcome message */
#define WELCOME_MSG "Hello, UART! Type something to echo back:\r\n"

/* Global Counter */
uint8_t txBuffer[BUFFER_SIZE];
uint8_t rxBuffer[BUFFER_SIZE];
volatile uint32_t rxBufferLength = 0;
uint16_t Global_Counter = 0;
volatile uint8 toggleLed = 0U;

/* External Variables and Functions */
extern ISR(STM_0_ISR);

void STM_Init(void)
{
    /* STM configuration, STM clock is determined by CGM settings default is FIRC 48MHz */
    /* STM timer is enabled here */
    /* STM pre-scaler = 48, so 1cnt=1uS*/
    Clock_Ip_EnableModuleClock(STM0_CLK);
    Stm_Ip_Init(STM0_INST, &STM_0_InitConfig_PB);

    /* Initialize STM0 compare channel 0 */
    Stm_Ip_InitChannel(STM0_INST, STM_0_ChannelConfig_PB);
    /* Start STM0 channel 0 ,set compare value, enable this channel, interrupt every 1ms */
    Stm_Ip_StartCounting (STM0_INST, STM0_CH0, 1000);

    /* Install IRQ handler for STM0 */
    IntCtrl_Ip_InstallHandler(STM0_IRQn, STM_0_ISR, NULL);
    IntCtrl_Ip_EnableIrq(STM0_IRQn);
}

void Stm0_Ch0_Callback(uint8 channel)
{
    (void)channel;
    Global_Counter++;
	if(Global_Counter>= 1000 && Global_Counter<= 2000)
	{
		toggleLed = 1U;
	}else if (Global_Counter>= 2000)
	{
		toggleLed = 2U;
		Global_Counter = 0;
	}
}

void LED_Init(void)
{
    //LEDS
    Siul2_Port_Ip_SetOutputBuffer(PORTA_H_HALF, 29, TRUE, PORT_MUX_AS_GPIO); //PTA29 as Output LED_RED
    Siul2_Port_Ip_SetOutputBuffer(PORTA_H_HALF, 30, TRUE, PORT_MUX_AS_GPIO); //PTA30 as Output LED_GREEN
}

int delayMS(struct Wait *delay) {
    if (delay->activeFlag == 0) {
        delay->currentTime = Global_Counter;
        delay->activeFlag = 1;
        return 0;
    } else {
        if ((Global_Counter - delay->currentTime) >= delay->delayTime) {
            delay->activeFlag = 0;
            return 1;
        }
    }
    return 0;
}

void LPUART_Init(void)
{
    Clock_Ip_EnableModuleClock(LPUART0_CLK);

    Lpuart_Uart_Ip_Init(LPUART_UART_INSTANCE, &Lpuart_Uart_Ip_xHwConfigPB_0);

    // Set up buffers and enable interrupts if necessary
    Lpuart_Uart_Ip_SetTxBuffer(LPUART_UART_INSTANCE, txBuffer, strlen((char *)txBuffer));
    Lpuart_Uart_Ip_SetRxBuffer(LPUART_UART_INSTANCE, rxBuffer, BUFFER_SIZE);
}

void UART_Error_Handler(Lpuart_Uart_Ip_StatusType Status)
{
    if (Status == LPUART_UART_IP_STATUS_ERROR)
    {
        Siul2_Dio_Ip_WritePin(LED_RED_PORT, LED_RED_PIN, 1); // Turn on RED LED
    }else if(Status == LPUART_UART_IP_STATUS_BUSY)
    {
    	 Siul2_Dio_Ip_WritePin(LED_GREEN_PORT, LED_GREEN_PIN, 1); // Turn on LED_GREEN
    }else if (Status == LPUART_UART_IP_STATUS_TIMEOUT)
    {
    	Siul2_Dio_Ip_WritePin(LED_BLUE_PORT, LED_BLUE_PIN, 1); // Turn on Blue LED
    }else if (Status == LPUART_UART_IP_STATUS_SUCCESS)
    {
    	Siul2_Dio_Ip_WritePin(LED_RED_PORT, LED_RED_PIN, 0); // Turn off RED LED
    	Siul2_Dio_Ip_WritePin(LED_BLUE_PORT, LED_BLUE_PIN, 0); // Turn off Blue LED
    	Siul2_Dio_Ip_WritePin(LED_GREEN_PORT, LED_GREEN_PIN, 0); // Turn off LED_GREEN
    }
}

int main(void)
{
    Clock_Ip_Init(&Clock_Ip_aClockConfig[0]);
    Clock_Ip_EnableModuleClock(SIUL2_CLK);

    IntCtrl_Ip_Init(&IntCtrlConfig_0);

    Siul2_Port_Ip_Init(NUM_OF_CONFIGURED_PINS0, g_pin_mux_InitConfigArr0);

    OsIf_Init(NULL);

    STM_Init();
    LED_Init();
    LPUART_Init();


    while (1)
    {
    	Lpuart_Uart_Ip_StatusType Uart_status;
        if (toggleLed == 1)
        {
            Siul2_Dio_Ip_WritePin(LED_GREEN_PORT, LED_GREEN_PIN, 1); // Turn on LED_GREEN_PIN

            Uart_status = Lpuart_Uart_Ip_SyncSend(LPUART_UART_INSTANCE, (uint8_t *)"LED On\n", 7, 500000);
            UART_Error_Handler(Uart_status);

        }else if (toggleLed == 2)
        {
            Siul2_Dio_Ip_WritePin(LED_GREEN_PORT, LED_GREEN_PIN, 0); // Turn off LED_GREEN_PIN

            Uart_status = Lpuart_Uart_Ip_SyncSend(LPUART_UART_INSTANCE, (uint8_t *)"LED Off\n", 8, 500000);
            UART_Error_Handler(Uart_status);
        }
    }
}

