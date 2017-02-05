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

#define EP_IN 1
#define EP_OUT 2

#define NUM_OF_DRIVES (1)

void (*stepper_step[NUM_OF_DRIVES])(uint16, int) = {
    Stepper_Step
};
uint8 (*stepper_status[NUM_OF_DRIVES])(void) = {
    Stepper_Status
};

volatile int stepper_irq_done[NUM_OF_DRIVES] = {0};

CY_ISR(step_irq) {
    LED_Write(LED_Read() ^ 1);
    stepper_irq_done[0] = 1;
}

enum commands_e {
    COMMAND_GET_INFO = 0x81,
    COMMAND_GET_STATUS = 0xA1,
    COMMAND_STEP = 0xA2,
    COMMAND_STEP_FINISHED = 0xA3
};

int main()
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    USB_Start(0, USB_5V_OPERATION);

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    Stepper_Start();
    StepperIRQ_StartEx(step_irq);
    
    while (0u == USB_GetConfiguration()) {}
    
    USB_EnableOutEP(EP_OUT);
    
    LED_Write(0);
    
    for(;;) {
        if (0u != USB_IsConfigurationChanged()) {
            if (0u != USB_GetConfiguration()) {
                USB_EnableOutEP(EP_OUT);
            }
        }
        
        for(int i = 0; i < NUM_OF_DRIVES; ++i) {
            if(stepper_irq_done[i]) {
                stepper_irq_done[i] = 0;
                uint8 status = stepper_status[i]();
                uint8 datain[3] = {COMMAND_STEP_FINISHED, i, status};
                USB_LoadInEP(EP_IN, datain, sizeof(datain));
            }
        }
        
        if (USB_OUT_BUFFER_FULL == USB_GetEPState(EP_OUT)) {
            uint16 len = USB_GetEPCount(EP_OUT);
            uint8 data[8];
            USB_ReadOutEP(EP_OUT, data, len);
            switch(data[0]) {
                case COMMAND_GET_INFO: {
                uint8 datain[2] = {COMMAND_GET_INFO, NUM_OF_DRIVES};
                USB_LoadInEP(EP_IN, datain, sizeof(datain));
                } break;
                case COMMAND_GET_STATUS: {
                uint8 stepper = data[1];
                if(stepper >= NUM_OF_DRIVES) break;
                uint8 status = stepper_status[stepper]();
                uint8 datain[3] = {COMMAND_GET_STATUS, stepper, status};
                USB_LoadInEP(EP_IN, datain, sizeof(datain));
                } break;
                case COMMAND_STEP: {
                uint8 stepper = data[1];
                if(stepper >= NUM_OF_DRIVES) break;
                uint16 steps = (data[2] << 8) | data[3];
                int dir = data[4];
                stepper_step[stepper](steps, dir);
                } break;
            }
        }
    }
}

/* [] END OF FILE */
