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

#include "isr.h"
#include "isrHandler.h"
// the isr handler for receiving info from the computer
CY_ISR(uartRxIsr) {
    // clear pending interrupt
    uint32_t intr = (uint32_t) UART0_GetRxInterruptSource();
    
    //clear interrupt
    //NOTE: the interrupt for the UART will stay high so long as 
    //the FIFO buffer has data in it. 
//    UART0_ClearRxInterruptSource(intr);
    RXISR_ClearPending(); 
    
    // queue this interrupt handler
    events |= EVENT_UART0;
}

/* [] END OF FILE */
