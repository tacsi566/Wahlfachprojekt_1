/*
 * Copyright (C) 2017-2018 Bas Stottelaar <basstottelaar@gmail.com>
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     cpu_efm32
 * @ingroup     drivers_periph_pm
 * @{
 *
 * @file
 * @brief       Implementation of the power management peripheral
 *
 * @author      Bas Stottelaar <basstottelaar@gmail.com>
 * @}
 */

#include "periph/pm.h"

#include "em_emu.h"

#define ENABLE_DEBUG 0
#include "debug.h"

void pm_set(unsigned mode)
{
    switch (mode) {
        case EFM32_PM_MODE_EM3:
            DEBUG_PUTS("[pm] enter EFM32_PM_MODE_EM3");
            /* after exiting EM3, clocks are restored */
            EMU_EnterEM3(true);
            break;
        case EFM32_PM_MODE_EM2:
            DEBUG_PUTS("[pm] enter EFM32_PM_MODE_EM2");
            /* after exiting EM2, clocks are restored */
            EMU_EnterEM2(true);
            break;
        case EFM32_PM_MODE_EM1:
            DEBUG_PUTS("[pm] enter EFM32_PM_MODE_EM1");
            /* wait for next event or interrupt */
            EMU_EnterEM1();
            break;
        default:
            /* no sleep at all  */
            break;
    }
}

void pm_off(void)
{
    EMU_EnterEM4();
}
