/**
 ******************************************************************************
 * @file        Timing.c
 * @author      ON Semiconductor USB-PD Firmware Team
 * @brief        Timer related functions
 * Software License Agreement:
 *
 * The software supplied herewith by ON Semiconductor (the Company)
 * is supplied to you, the Company's customer, for exclusive use with its
 * USB Type C / USB PD products.  The software is owned by the Company and/or
 * its supplier, and is protected under applicable copyright laws.
 * All rights are reserved. Any use in violation of the foregoing restrictions
 * may subject the user to criminal sanctions under applicable laws, as well
 * as to civil liability for the breach of the terms and conditions of this
 * license.
 *
 * THIS SOFTWARE IS PROVIDED IN AN AS IS CONDITION. NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 * TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 * IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *******************************************************************************
 */

#include "Timing.h"
#include <Arduino.h>
//#include <variant.h>

#define TIMER_PRESCALER_DIV 16

extern FSC_BOOL haveINTReady;

#include "./core/core.h"

extern "C"
{
	FSC_U32 platform_get_system_time(void)
	{
		return millis();
	}
}

void SetTimeInterrupt(FSC_U32 DIS)
{
	//	Todo @adam

	// Calculate compare value(s)
	/*
	uint32_t SYSCLOCK_HZ = (uint32_t) VARIANT_MCK;
	uint32_t TIMCLK_Hz = SYSCLOCK_HZ / TIMER_PRESCALER_DIV;
	uint32_t NANOSECONDS_PER_TICK = 1000000000 / TIMCLK_Hz;
	uint16_t CC1_value = (uint16_t)((float)(1000) * microseconds / (float)NANOSECONDS_PER_TICK);

	// Set capture compare 1
	g_LP_fusbTCC->CC[1].reg = CC1_value;
	while (g_LP_fusbTCC->SYNCBUSY.reg & TCC_SYNCBUSY_MASK);	
	
	// Set per value for overflow reset
	g_LP_fusbTCC->PER.reg = CC1_value + 1; //PER_value;
	while (g_LP_fusbTCC->SYNCBUSY.reg & TCC_SYNCBUSY_MASK);
	
	// Retrigger timer
	g_LP_fusbTCC->CTRLBSET.reg = TCC_CTRLBSET_CMD_RETRIGGER;
	*/
}

extern "C"
{
	void platform_delay(FSC_U32 microseconds)
	{
		delayMicroseconds(microseconds);
	}
}

extern "C"
{
	void platform_delay_10us(FSC_U32 tenMicroSecondCounter)
	{
		platform_delay(tenMicroSecondCounter * 10);
	}
}


void InitializeOneShotTimer(void)
{
}

extern "C"
{
	FSC_U32 platform_get_log_time(void)
	{
		/* This packs seconds and tenths of milliseconds into one 32-bit value. */
		//return ((FSC_U32) (TIM3->CNT) << 16) + (FSC_U32) (TIM1->CNT);
		
		return 0;
	}
}

/**
  * @brief  This function handles timer timeout interrupt request on CC1
  * @param  None
  * @retval None
  */
void TCC1_Handler(void)
{
// 	// Capture compare 0
// 	if (g_LP_fusbTCC->INTFLAG.bit.MC0 == 1)
// 	{
// 		g_LP_fusbTCC->INTFLAG.bit.MC0 = 1;
// 		//pinPeripheral(g_LP_pinId.pwmPin, g_LP_pinPwm_EPioType);
// 	}

// is this needed?

// 	// Capture compare 1
// 	if (g_LP_fusbTCC->INTFLAG.bit.MC1 == 1)
// 	{
// 		g_LP_fusbTCC->INTFLAG.bit.MC1 = 1;
// 		
// 		if(true /*g_LP_pinPwm_oneShotModeEnabled*/)
// 		{
// 			g_LP_fusbTCC->CTRLBSET.reg = TCC_CTRLBSET_CMD_STOP;
// 		}
// 		//pinMode(g_LP_pinId.pwmPin, OUTPUT);
// 		//digitalWrite(g_LP_pinId.pwmPin, LOW);
// 		
// 		haveINTReady = TRUE;
// 	}

//     TIM2->DIER &= ~TIM_DIER_CC1IE;
//     TIM2->CCR1 = 0;
//     TIM2->SR = 0;
}