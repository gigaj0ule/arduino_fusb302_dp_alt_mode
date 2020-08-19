/**
 *******************************************************************************
 * @file        timer.h
 * @author      ON Semiconductor USB-PD Firmware Team
 * @brief       Implements a generic timer countdown mechanism.
 *
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
#include "../compileFlags.h"

#ifndef _FSC_TIMER_H_
#define _FSC_TIMER_H_

#include "platform.h"

#define TIMER_DISABLE_COUNT 4   /* Should cause the timer to be disabled
                                 * during core_get_next_timeout calls.
                                 */

/* Struct object to contain the timer related members */
struct TimerObj {
  FSC_U32 starttime_;           /* Time-stamp when timer started */
  FSC_U32 period_;              /* Timer period */
  FSC_U8  disablecount_;        /* Auto-disable timers if they keep getting
                                 * checked and aren't explicitly disabled.
                                 */
};

/**
 * @brief Start the timer
 *
 * Records the current system timestamp as well as the time value
 *
 * @param Timer object
 * @param time non-zero, in units of (milliseconds / (platform scale value)).
 * @return None
 */
void TimerStart(struct TimerObj *obj, FSC_U32 time);

/**
 * @brief Restart the timer using the last used delay value.
 *
 * @param Timer object
 * @return None
 */
void TimerRestart(struct TimerObj *obj);

/**
 * @brief Set time and period to zero to indicate no current period.
 *
 * @param Timer object
 * @return TRUE if the timer is currently disabled
 */
void TimerDisable(struct TimerObj *obj);
FSC_BOOL TimerDisabled(struct TimerObj *obj);

/**
 * @brief Determine if timer has expired
 *
 * Check the current system time stamp against (start_time + time_period)
 *
 * @param Timer object
 * @return TRUE if time period has finished.
 */
FSC_BOOL TimerExpired(struct TimerObj *obj);

/**
 * @brief Returns the time remaining in microseconds, or zero if disabled/done.
 *
 * @param Timer object
 */
FSC_U32 TimerRemaining(struct TimerObj *obj);

#endif /* _FSC_TIMER_H_ */

