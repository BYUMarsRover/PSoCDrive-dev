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

void myIsr() {
    uint32_t intr = UART_1_GetRxInterruptSourceMasked();
    UART_1_ClearRxInterruptSource(intr);
    UART_1_UartPutChar(UART_1_UartGetChar());
}

/* [] END OF FILE */
