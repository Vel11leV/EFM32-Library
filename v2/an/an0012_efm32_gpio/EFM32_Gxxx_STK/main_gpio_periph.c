/*****************************************************************************
 * @file main_gpio_periph.c
 * @brief GPIO Demo Application
 * @author Silicon Labs
 * @version 1.07
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
#include "em_cmu.h"
#include "em_emu.h"
#include "em_gpio.h"
#include "em_chip.h"

/**************************************************************************//**
 * @brief  Main function
 * Main is called from __iar_program_start, see assembly startup file
 *****************************************************************************/
int main(void)
{  
  /* Initialize chip */
  CHIP_Init();
  
  /* Enable clock for GPIO module */
  CMU_ClockEnable(cmuClock_GPIO, true);

  /* Set PC12 and PD8 as outputs so they can be 
  overridden by the peripheral, in this case the CMU */  
  GPIO_PinModeSet(gpioPortC, 12, gpioModePushPull, 0);
  GPIO_PinModeSet(gpioPortD, 8, gpioModePushPull, 0);

  /* Enable Low Frequency RC Oscillator (LFRCO) and 
  wait until it is stable*/
  CMU_OscillatorEnable(cmuOsc_LFRCO, true, true);
  
  /* Select Clock Output 0 as High Frequency RC without prescaling
  (14 Mhz) and Clock Output 1 as Low Frequency RC(32.768 KHz) */
  CMU->CTRL = CMU->CTRL | CMU_CTRL_CLKOUTSEL1_LFRCO | CMU_CTRL_CLKOUTSEL0_HFRCO;
  
  /* Route the Clock output pins to Location 1 and enable them */
  CMU->ROUTE = CMU_ROUTE_LOCATION_LOC1 | CMU_ROUTE_CLKOUT1PEN | CMU_ROUTE_CLKOUT0PEN;  
  
  while(1);
 
}

