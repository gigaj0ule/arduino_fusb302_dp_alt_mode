/**
 ******************************************************************************
 * @file        FSCTypes.h
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

#ifndef FSCTYPES_H
#define FSCTYPES_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Define compiler macros */
#if defined ( __GNUC__ )
  #define __ASM            __asm
  #define __INLINE         inline
  #define __STATIC_INLINE  static inline
  #define __PACKED         __attribute__((packed))
  #define __ALIGNED(n)     __attribute__((aligned(n)))
#else
  #define __ASM
  #define __INLINE
  #define __STATIC_INLINE
  #define __PACKED
  #define __ALIGNED(n)
#endif

 /* Define Boolean types */
typedef enum _BOOL
{
    FALSE = 0,
    TRUE
} FSC_BOOL;

/* Signed types */
typedef int8_t      FSC_S8;
typedef int16_t		FSC_S16;
typedef int32_t		FSC_S32;

/* Unsigned types */
typedef uint8_t     FSC_U8;
typedef uint16_t	FSC_U16;
typedef uint32_t	FSC_U32;

#ifdef __cplusplus
}
#endif

#endif /* FSCTYPES_H */

