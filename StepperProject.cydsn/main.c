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

volatile static int dir = 0;

CY_ISR(step_irq) {
    LED_Write(LED_Read() ^ 1);
    if(Stepper_Status() & Stepper_STATUS_STOP_DETECTED_MASK)
        dir ^= 1;
    Stepper_Step(512, dir);
}

int main()
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    Stepper_Start();
    StepperIRQ_StartEx(step_irq);
    
    Stepper_Step(512, dir);
    
    for(;;)
    {
        /*LED_Write(LED_Read() ^ 1);
        Stepper_Step(512, dir);
        while((Stepper_Status() & Stepper_STATUS_DONE_MASK) == 0);
        if(Stepper_Status() & Stepper_STATUS_STOP_DETECTED_MASK)
            dir ^= 1;*/
    }
}

/* [] END OF FILE */
