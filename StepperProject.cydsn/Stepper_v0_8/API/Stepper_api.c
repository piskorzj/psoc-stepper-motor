/* ========================================
 *
 * Jakub Piskorz <piskorzj@gmail.com>
 *
 * ========================================
*/
#include "`$INSTANCE_NAME`.h"
#include <project.h>

#define `$INSTANCE_NAME`_CTL_START  (0x01)
#define `$INSTANCE_NAME`_CTL_ENABLE (0x02)
#define `$INSTANCE_NAME`_CTL_DIR(x) (((x)&0x1) << 2)


void `$INSTANCE_NAME`_Start(void) {
    `$INSTANCE_NAME`_STEP_COUNT_Start();
    //`$INSTANCE_NAME`_STEP_CTL_Write(`$INSTANCE_NAME`_CTL_ENABLE);
    `$INSTANCE_NAME`_STEP_STATUS_InterruptEnable();
}

void `$INSTANCE_NAME`_Step(uint16 steps, int dir) {
    `$INSTANCE_NAME`_STEP_COUNT_WritePeriod(steps);
    //CyDelay(10);
    `$INSTANCE_NAME`_STEP_CTL_Write(`$INSTANCE_NAME`_CTL_START |
                                    `$INSTANCE_NAME`_CTL_ENABLE| 
                                    `$INSTANCE_NAME`_CTL_DIR(dir));
}

uint8 `$INSTANCE_NAME`_Status(void) {
    return `$INSTANCE_NAME`_STEP_STATUS_Read();    
}

/* [] END OF FILE */
