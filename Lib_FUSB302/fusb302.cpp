/**
 ******************************************************************************
 * @file        main.c
 * @author      ON Semiconductor USB-PD Firmware Team
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
#include <Arduino.h>
#include <Wire.h>

#include "./compileFlags.h"
#include "./FSCTypes.h"
#include "./fusb302.h"

extern "C"
{
#include "./core/core.h"
#include "./core/modules/dpm.h"
#include "./core/modules/HostComm.h"
#include "./core/platform.h"
#include "./core/vdm/DisplayPort/dp.h"
};

#include "./Timing.h"

volatile FSC_BOOL haveINTReady = FALSE;

#ifdef FSC_DEBUG
volatile FSC_BOOL haveUSBInMsg = FALSE;
#endif /* FSC_DEBUG */

static DevicePolicyPtr_t dpm;
static Port_t ports[NUM_PORTS];           /* Array of ports */


FUSB302_ FUSB302;

FUSB302_::FUSB302_(void)
{
}

void FUSB302_:: begin(int intn_pin)
{
	// Set-up Variables
	this->pin_fusb_intn = intn_pin;
	this->pd_contract_good = false;
	
	// Attach pins
	pinMode(this->pin_fusb_intn, INPUT_PULLUP);
	attachInterrupt(this->pin_fusb_intn, intCallback, FALLING);

	InitializeOneShotTimer();
	
	Wire.begin();

    DPM_Init(&dpm);

    ports[0].dpm = dpm;
    ports[0].PortID = 0;
	
	core_initialize(&ports[0], FUSB300SlaveAddr);
	core_enable_pd(&ports[0], TRUE);

    DPM_AddPort(dpm, &ports[0]);
}


void FUSB302_:: loop(void)
{
//#if 1
#ifdef FSC_POLLING_MODE
        haveINTReady = TRUE;
#endif /* FSC_POLLING_MODE */

        /* Run the Type-C state machine */
        if( haveINTReady
#ifdef FSC_DEBUG
                 || haveUSBInMsg
#endif /* FSC_DEBUG */
        )
        {
            haveINTReady = FALSE;

            /* Optional: Enable system timer(s) here if they were previously
             * disabled while in Idle mode.
             */
            core_state_machine(&ports[0]);

            /*
             * It is possible for the state machine to go into idle mode with
             * the interrupt pin still low and as a result the edge-sensitive
             * IRQ won't get triggered.  Check here before returning to wait
             * on the IRQ.
             */
            if(platform_get_device_irq_state(ports[0].PortID))
            {
                haveINTReady = TRUE;
            }
            else
            {
                /* If needed, enable timer interrupt before idling */
                this->timer_value = core_get_next_timeout(&ports[0]);

                if (this->timer_value > 0)
                {
                    if (this->timer_value == 1)
                    {
                        /* A value of 1 indicates that a timer has expired
                         * or is about to expire and needs further processing.
                         */
                        haveINTReady = TRUE;
                    }
                    else
                    {
                        /* A non-zero time requires a future timer interrupt */
                        SetTimeInterrupt(this->timer_value);
                    }
                }
                else
                {
                    /* Optional: Disable system timer(s) here to save power
                     * if needed while in Idle mode.
                     */
                }
            }
			
			
			// Now update external states
			this->pd_contract_good = ports[0].PolicyHasContract;
        }

	#ifdef FSC_DEBUG
			if (haveUSBInMsg)
			{
			  /* Process the message */
			  HCom_Process();

			  Serial.print((const char *)HCom_OutBuf());

			  haveUSBInMsg = FALSE;
			}
	#endif /* FSC_DEBUG */
}


void FUSB302_:: displayPort_configure(bool hpd_state)
{
// 	if(hpd_state == true)
// 	{
// 		ports[0].DpStatus.HpdState = 1;		
// 		ports[0].DpStatus.IrqHpd = 0;
// 		ports[0].DpEnabled = TRUE;
// 	}
// 	else
// 	{
// 		// ports[0].DpStatus.Connection = DP_CONN_NEITHER;
// 		ports[0].DpStatus.HpdState = 0;
// 		ports[0].DpStatus.IrqHpd = 1;
// 		ports[0].DpEnabled = FALSE;
// 	}
// 	
// 	doDataObject_t svdm_out = {0};
// 			
// 	svdm_out.SVDM.SVID = 0xFF01; // displayport
// 	svdm_out.SVDM.VDMType = STRUCTURED_VDM;
// 	svdm_out.SVDM.Version = (ports[0].PdRevContract == USBPDSPECREV2p0) ? V1P0 : V2P0;
// 	svdm_out.SVDM.CommandType = INITIATOR;
// 	svdm_out.SVDM.Command = ATTENTION;
// 			
// 	sendStatusData(&ports[0], svdm_out);
// 			
// 	haveINTReady = TRUE;
}

#ifdef FSC_HAVE_DP
FSC_BOOL platform_dp_enable_pins(FSC_BOOL enable, FSC_U32 config)
{
	return TRUE;
}

void platform_dp_status_update(FSC_U32 status)
{
	ports[0].DisplayPortData.DpStatus.HpdState = TRUE;
	ports[0].DisplayPortData.DpEnabled = TRUE;
}
#endif /* FSC_HAVE_DP */

void intCallback(void)
{
    __asm__ ("nop");
	haveINTReady = TRUE;
}
