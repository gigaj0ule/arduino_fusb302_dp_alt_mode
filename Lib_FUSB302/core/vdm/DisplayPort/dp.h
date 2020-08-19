/*******************************************************************************
 * @file     dp.h
 * @author   USB PD Firmware Team
 *
 * Copyright 2018 ON Semiconductor. All rights reserved.
 *
 * This software and/or documentation is licensed by ON Semiconductor under
 * limited terms and conditions. The terms and conditions pertaining to the
 * software and/or documentation are available at
 * http://www.onsemi.com/site/pdf/ONSEMI_T&C.pdf
 * ("ON Semiconductor Standard Terms and Conditions of Sale, Section 8 Software").
 *
 * DO NOT USE THIS SOFTWARE AND/OR DOCUMENTATION UNLESS YOU HAVE CAREFULLY
 * READ AND YOU AGREE TO THE LIMITED TERMS AND CONDITIONS. BY USING THIS
 * SOFTWARE AND/OR DOCUMENTATION, YOU AGREE TO THE LIMITED TERMS AND CONDITIONS.
 ******************************************************************************/
#include "compileFlags.h"

#ifdef FSC_HAVE_DP

#ifndef __DISPLAYPORT_DP_H__
#define __DISPLAYPORT_DP_H__

#include "platform.h"
#include "PD_Types.h"
#include "vdm_types.h"
#include "dp_types.h"
#include "typeCPort.h"

void DP_Initialize(struct cPort *port);

/*  Interface used by VDM/policy engines */
/*  Initiate status request - call to get status of port partner */
void DP_RequestPartnerStatus(struct cPort *port);
/*  Initiate config request - call to configure port partner */
void DP_RequestPartnerConfig(struct cPort *port, DisplayPortConfig_t in);

/** Logic to decide capability to accecpt from UFP_U */
FSC_BOOL DP_EvaluateSinkCapability(struct cPort *port, FSC_U32 mode_in);

/*  Process special DisplayPort commands. */
/*  Returns TRUE when the message isn't processed and FALSE otherwise */
FSC_BOOL DP_ProcessCommand(struct cPort *port, FSC_U32* arr_in);

/*  Internal helper functions */
/*  Send status data to port partner */
void DP_SendPortStatus(struct cPort *port, doDataObject_t svdmh_in);

/*  Reply to a config request (to port partner) */
void DP_SendPortConfig(struct cPort *port, doDataObject_t svdmh_in,
                       FSC_BOOL success);
void DP_SendAttention(struct cPort *port);

void DP_SetPortMode(struct cPort *port, DisplayPortMode_t conn);

/*  Internal DP functionality to be customized per system */
void DP_ProcessPartnerAttention(struct cPort *port, DisplayPortStatus_t stat);
void DP_ProcessConfigResponse (struct cPort *port, FSC_BOOL success);
FSC_BOOL DP_ProcessConfigRequest(struct cPort *port, DisplayPortConfig_t config);
void DP_UpdatePartnerStatus(struct cPort *port, DisplayPortStatus_t status,
                            FSC_BOOL success);

#endif /* __DISPLAYPORT_DP_H__ */

#endif // FSC_HAVE_DP
