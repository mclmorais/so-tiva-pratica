//*****************************************************************************
//
// hello.c - Simple hello world example.
//
// Copyright (c) 2013-2014 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
//
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
//
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
//
// This is part of revision 2.1.0.12573 of the EK-TM4C1294XL Firmware Package.
//
//*****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include "hw_memmap.h"
#include "hw_types.h"
#include "driverlib/gpio.h"
#include "drivers/pinout.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "driverlib/systick.h"

#include "tcb/ppos.h"
#include "tcb/pingpong-tasks1.h"
#include "tcb/pingpong-tasks2.h"
#include "tcb/pingpong-tasks3.h"
#include "tcb/pingpong-dispatcher.h"
#include "tcb/pingpong-scheduler.h"
#include "tcb/pingpong-preempcao.h"

#include "debug.h"

#include <stdlib.h>

uint32_t g_ui32SysClock;

int led_counter = 0;

//*****************************************************************************
//
// The error routine that is called if the driver library encounters an error.
//
//*****************************************************************************
#ifdef DEBUG
void __error__(char *pcFilename, uint32_t ui32Line)
{
  UARTprintf("%s %d\n", pcFilename, ui32Line);
}
#endif

//void flainsqsen()
//{

//   if (++led_counter >= 100)
//   {
//    led_counter = 0;
//    LEDWrite(CLP_D1, led_blink);
//    LEDWrite(CLP_D2, !led_blink);
//    led_blink = !led_blink;
//   }
//}



void ConfigureUART(void)
{
  // Enable the GPIO Peripheral used by the UART.
  ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

  // Enable UART0
  ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

  // Configure GPIO Pins for UART mode.
  ROM_GPIOPinConfigure(GPIO_PA0_U0RX);
  ROM_GPIOPinConfigure(GPIO_PA1_U0TX);
  ROM_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
  ROM_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_2);

  // Initialize the UART for console I/O.
  UARTStdioConfig(0, 115200, g_ui32SysClock);
}

int main(void)
{
  // Run from the PLL at 120 MHz.
  g_ui32SysClock = MAP_SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ | SYSCTL_OSC_MAIN | SYSCTL_USE_PLL | SYSCTL_CFG_VCO_480), 120000000);

  SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);

  // Configure the device pins.
  PinoutSet(false, false);

  // Enable the GPIO pins for the LED D1 (PN1).
  ROM_GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_1);
  ROM_GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_2);

  // Initialize the UART.
  ConfigureUART();
  UARTprintf("Clock:%i\n", g_ui32SysClock);
  SysTickPeriodSet(g_ui32SysClock / 1000);
  SysTickIntRegister(&task_interrupt);
  SysTickEnable();
  //SysTickIntRegister(&flainsqsen);
  ppos_init();
  UARTprintf("----------Inicializacao completa----------\n");

  // TestePingPong1();
  // TestePingPong2();
  // TestePingPong3();
  // testedispatcher();
  //teste_scheduler();
  PingPongPreempcao();

  UARTprintf("----------Termino: loop infinito----------\n");
  //SysTickIntRegister(&flainsqsen);
  while (1)
  {
 //  ui32Value = SysTickValueGet();

    // //  UARTprintf("%i!!!\n", ___aux);

    // //
    // // Turn on D1.
    // //
    // LEDWrite(CLP_D1, 1);
    // LEDWrite(CLP_D2, 0);

    // //
    // // Delay for a bit.
    // //
    // SysCtlDelay(g_ui32SysClock / 10 / 3);

    // //
    // // Turn off D1.
    // //
    // LEDWrite(CLP_D1, 0);
    // LEDWrite(CLP_D2, 1);
    // //
    // // Delay for a bit.
    // //
    // SysCtlDelay(g_ui32SysClock / 10 / 3);
  }
}
