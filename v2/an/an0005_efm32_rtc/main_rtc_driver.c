/*****************************************************************************
 * @file main_rtc_driver.c
 * @brief Real Time Counter Driver Demo Application
 * @author Silicon Labs
 * @version 1.08
 ******************************************************************************
 * @section License
 * <b>(C) Copyright 2014 Silicon Labs, http://www.silabs.com</b>
 *******************************************************************************
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 * DISCLAIMER OF WARRANTY/LIMITATION OF REMEDIES: Silicon Labs has no
 * obligation to support this Software. Silicon Labs is providing the
 * Software "AS IS", with no express or implied warranties of any kind,
 * including, but not limited to, any implied warranties of merchantability
 * or fitness for any particular purpose or warranties against infringement
 * of any proprietary rights of a third party.
 *
 * Silicon Labs will not be liable for any consequential, incidental, or
 * special damages, or any other relief, or for any claim by any third party,
 * arising from your use of this Software.
 *
 ******************************************************************************/
 
#include "em_device.h"
#include "em_chip.h"
#include "em_rtc.h"
#include "em_cmu.h"
#include "em_emu.h"

#include "rtcdrv.h"

/* Defines*/
#define WAKEUP_INTERVAL_MS            500

/**************************************************************************//**
 * @brief  Main function
 *****************************************************************************/
int main(void)
{
  /* Initialize chip */
  CHIP_Init();
  
  /* Setup RTC with selected clock source and prescaler. */
  RTCDRV_Setup(cmuSelect_LFRCO, cmuClkDiv_16);

  /* Disable LFB clock domains to save power */
  CMU->LFCLKSEL &= ~_CMU_LFCLKSEL_LFB_MASK;     
  
  while (1)
  {
    /* Delay WAKEUP_INTERVAL_MS ms, enter EM2 while waiting */
    RTCDRV_Delay(WAKEUP_INTERVAL_MS ,true);
  }
}

