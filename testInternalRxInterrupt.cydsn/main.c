/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <project.h>
#include "isr.h"

/*
CY_ISR(uartIsr) {
    uint32_t intr = UART_1_GetRxInterruptSourceMasked();
    UART_1_ClearRxInterruptSource(intr);
    
    // echo...
    UART_1_UartPutChar(UART_1_UartGetChar());
}
*/

int main()
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    UART_1_Start();
    UART_1_SetCustomInterruptHandler(myIsr);
    //UART_1_SCB_IRQ_StartEx(uartIsr);
    for(;;)
    {
        /* Place your application code here. */
        LED0_Write(!LED0_Read());
        CyDelay(1000);
    }
}

/* [] END OF FILE */
