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

int main()
{
    // CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    LED0_Write(0);
    LED1_Write(1);
    timer_clock_Start();
    PWM_1_Start();
    for(;;)
    {
        PWM_1_WriteCompare(1000);
        LED0_Write(!LED0_Read());
        LED1_Write(!LED1_Read());
        CyDelay(1000);
        PWM_1_WriteCompare(2000);
        CyDelay(1000);
    }
}

/* [] END OF FILE */
