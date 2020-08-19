/**
 ******************************************************************************
 * @file        Timing.h
 * @author      ON Semiconductor USB-PD Firmware Team
 * @brief       Timer related functions
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

#ifndef TIMING_H
#define TIMING_H

#include "FSCTypes.h"

/**
 * @brief Using the match interrupt feature, set up an interrupt
 * in X microseconds.
 * @param microseconds time in microsecond resolution
 * @return None
 */
void SetTimeInterrupt(FSC_U32 microseconds);

/*
 * @brief Time-stamp timer that is currently implemented as linked
 * 1 second and 0.1ms counters.
 * @param None
 * @return None
 */
void InitializeOneShotTimer(void);

/*
 * @brief The log timestamp is returned as - Upper 16: Seconds, Lower 16: 0.1ms.
 * @param None
 * @return None
 */
extern "C"
{
FSC_U32 platform_get_log_time(void);
}

#endif /* TIMING_H */
