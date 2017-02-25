/* ========================================
 *
 * Jakub Piskorz <piskorzj@gmail.com>
 *
 * ========================================
*/
#include "`$INSTANCE_NAME`.h"
#include <project.h>

#define `$INSTANCE_NAME`_CTL_START  (0x01)
#define `$INSTANCE_NAME`_CTL_DIR(x) (((x)&0x1) << 1)


void `$INSTANCE_NAME`_Start(void) {
    `$INSTANCE_NAME`_STEP_STATUS_InterruptEnable();
}

void `$INSTANCE_NAME`_Step(uint16 steps, int dir) {
    //`$INSTANCE_NAME`_STEP_COUNT_WritePeriod(steps);
    *`$INSTANCE_NAME`_Stepper_core_Stepper_datapath_F0_PTR = steps;
    //CyDelay(10);
    `$INSTANCE_NAME`_STEP_CTL_Write(`$INSTANCE_NAME`_CTL_START |
                                    `$INSTANCE_NAME`_CTL_DIR(dir));
}

uint8 `$INSTANCE_NAME`_Status(void) {
    return `$INSTANCE_NAME`_STEP_STATUS_Read();    
}

/* [] END OF FILE */
