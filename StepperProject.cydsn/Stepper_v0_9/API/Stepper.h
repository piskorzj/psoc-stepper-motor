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

#ifndef `$INSTANCE_NAME`_STEPPER_H
#define `$INSTANCE_NAME`_STEPPER_H

    #include "cytypes.h"
    #include "cyfitter.h"
    
    #define `$INSTANCE_NAME`_STATUS_DONE_MASK (0x01)
    #define `$INSTANCE_NAME`_STATUS_STOP_DETECTED_MASK (0x02)
    #define `$INSTANCE_NAME`_STATUS_STOP_DIR_MASK (0x04)
    #define `$INSTANCE_NAME`_STATUS_FAILED_START_MASK (0x08)
    
    void `$INSTANCE_NAME`_Start(void);
    void `$INSTANCE_NAME`_Step(uint16 steps, int dir);
    
    uint8 `$INSTANCE_NAME`_Status(void);
    
#endif/*`$INSTANCE_NAME`_STEPPER_H*/

/* [] END OF FILE */
