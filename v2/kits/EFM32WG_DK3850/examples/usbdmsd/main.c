/**************************************************************************//**
 * @file main.c
 * @brief Mass Storage Device example.
 * @version 3.20.5
 ******************************************************************************
 * @section License
 * <b>(C) Copyright 2014 Silicon Labs, http://www.silabs.com</b>
 *******************************************************************************
 *
 * This file is licensed under the Silabs License Agreement. See the file
 * "Silabs_License_Agreement.txt" for details. Before using this software for
 * any purpose, you must agree to the terms of that agreement.
 *
 ******************************************************************************/

#include <stdio.h>
#include "em_device.h"
#include "em_usb.h"
#include "em_assert.h"
#include "em_cmu.h"
#include "em_emu.h"
#include "em_gpio.h"
#include "bsp.h"
#include "bsp_trace.h"
#include "retargetserial.h"
#include "msdd.h"
#include "msddmedia.h"
#include "usbconfig.h"

/**************************************************************************//**
 *
 * This example shows how a Mass Storage Device (MSD) can be implemented.
 *
 * Different kinds of media can be used for data storage. Modify the
 * MSD_MEDIA #define macro in msdmedia.h to select between the different ones.
 *
 *****************************************************************************/

#if defined( BUSPOWERED )
#if ( ( MSD_MEDIA==MSD_PSRAM_MEDIA ) || ( MSD_MEDIA==MSD_SDCARD_MEDIA ) )
#error "Illegal combination of BUSPOWERED and MSD_MEDIA type."
#endif
#endif

/**************************************************************************//**
 * @brief main - the entrypoint after reset.
 *****************************************************************************/
int main( void )
{
#if !defined(BUSPOWERED)
  BSP_Init(BSP_INIT_DEFAULT);   /* Initialize DK board register access */

  /* If first word of user data page is non-zero, enable eA Profiler trace */
  BSP_TraceProfilerSetup();
#endif

  CMU_ClockSelectSet( cmuClock_HF, cmuSelect_HFXO );
  CMU_OscillatorEnable(cmuOsc_LFXO, true, false);

#if !defined(BUSPOWERED)
  RETARGET_SerialInit();        /* Initialize DK UART port */
  RETARGET_SerialCrLf( 1 );     /* Map LF to CRLF          */
  printf( "\nEFM32 Mass Storage Device example\n" );
#endif

  if ( !MSDDMEDIA_Init() )
  {
#if !defined(BUSPOWERED)
    printf( "\nMedia error !\n" );
#endif
    EFM_ASSERT( false );
    for( ;; ){}
  }

  MSDD_Init(gpioPortE, 1);

  for (;;)
  {
    if ( MSDD_Handler() )
    {
      /* There is no pending activity in the MSDD handler.  */
      /* Enter sleep mode to conserve energy.               */

      if ( USBD_SafeToEnterEM2() )
        EMU_EnterEM2(true);
      else
        EMU_EnterEM1();
    }
  }
}
