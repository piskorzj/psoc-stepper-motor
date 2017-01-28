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
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    CyDelay(2000);
    STEP_COUNT_Start();
    STEP_CTL_Write(2);
    CyDelay(2000);
    unsigned int togle = 0;
    for(;;)
    {
        STEP_COUNT_WritePeriod(2048);
        STEP_CTL_Write(3 | togle);
        LED_Write(LED_Read() ^ 1);
        //togle ^= 0x4;
        while((STEP_STATUS_Read() & 0x1) == 0);
        CyDelay(2000);
        
        STEP_COUNT_WritePeriod(2048);
        STEP_CTL_Write(3 | togle);
        LED_Write(LED_Read() ^ 1);
        togle ^= 0x4;
        while((STEP_STATUS_Read() & 0x1) == 0);
        CyDelay(2000);
    }
}

/* [] END OF FILE */
