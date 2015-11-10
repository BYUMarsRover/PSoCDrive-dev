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
//CY_ISR(uartRxIsr) {
void uartRxIsr() {
    // clear pending interrupt
    uint32_t intr = (uint32_t) UART0_GetRxInterruptSourceMasked();
    UART0_ClearRxInterruptSource(intr);
    
    // queue this interrupt handler
    events |= EVENT_UART0;
}

/* [] END OF FILE */
