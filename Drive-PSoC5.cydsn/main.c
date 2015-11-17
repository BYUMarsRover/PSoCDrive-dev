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
#include "isrHandler.h"

int main()
{    
    CyGlobalIntEnable; /* Enable global interrupts. */
    UART0_Start();
    RXISR_StartEx(uartRxIsr);
    Clock_1_Start();
    Drive_Start();
    Gimbal_Start();
    // TickTimer_Start(); - not using this yet.
    
    // TODO: I may need to increase the size of the uart rx buffer.
    
    while (1) {
        // any events pending?
        if (events) {
            // uart rx handler
            if (events & EVENT_UART0) {
                uart0_eventHandler();
            }
           // else if (events & EVENT1) {
           //     event1Handler();
           // }
        }
    }
}

/* [] END OF FILE */
