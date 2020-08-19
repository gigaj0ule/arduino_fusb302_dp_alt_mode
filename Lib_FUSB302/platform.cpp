/*
 * platform.c
 *
 * Created: 8/16/2018 10:56:59 PM
 *  Author: root
 */ 

#include "./core/platform.h"

#include <Arduino.h>
#include <Wire.h>

#include "../pin_settings.h"

extern "C"
{
	void platform_set_vbus_lvl_enable(FSC_U8 port, VBUS_LVL level, FSC_BOOL enable,
	FSC_BOOL disableOthers)
	{
		if (level == VBUS_LVL_5V)
		{
			//         /* Enable/Disable the 5V Source */
			//         HAL_GPIO_WritePin( VBUS_PORT, VBUS_5V_PIN,
			//                            enable ? GPIO_PIN_SET : GPIO_PIN_RESET );
			//
			//         if (disableOthers)
			//         {
			//           HAL_GPIO_WritePin( VBUS_PORT, VBUS_HV_PIN, GPIO_PIN_RESET );
			//         }
		}
		else if (level == VBUS_LVL_HV)
		{
			//         /* Enable/Disable the HV Source */
			//         HAL_GPIO_WritePin( VBUS_PORT, VBUS_HV_PIN,
			//                            enable ? GPIO_PIN_SET : GPIO_PIN_RESET );
			//
			//         if (disableOthers)
			//         {
			//           HAL_GPIO_WritePin( VBUS_PORT, VBUS_5V_PIN, GPIO_PIN_RESET );
			//         }
		}

		/* Turn off all levels, if requested */
		if ((level == VBUS_LVL_ALL) && (enable == FALSE))
		{
			//       HAL_GPIO_WritePin( VBUS_PORT, VBUS_5V_PIN, GPIO_PIN_RESET );
			//       HAL_GPIO_WritePin( VBUS_PORT, VBUS_HV_PIN, GPIO_PIN_RESET );
		}
	}


	void platform_set_pps_voltage(FSC_U8 port, FSC_U32 mv)
	{
		// #ifdef FSC_HAVE_PPS_SOURCE
		//   if (mv == 0)
		//   {
		//     FAN6295_SetEnable(FALSE);
		//     FAN6295_SetVoltage(250); /* Set to 5V - setting 0V causes POR */
		//   }
		//   else
		//   {
		//     FAN6295_SetVoltage(mv);
		//     FAN6295_SetEnable(TRUE);
		//   }
		// #endif /* FSC_HAVE_PPS_SOURCE */
	}

	FSC_U16 platform_get_pps_voltage(FSC_U8 port)
	{
		return 0;
	}

	void platform_set_pps_current(FSC_U8 port, FSC_U32 ma)
	{
		// #ifdef FSC_HAVE_PPS_SOURCE
		//     FAN6295_SetILimit(ma);
		// #endif /* FSC_HAVE_PPS_SOURCE */
	}

	FSC_U16 platform_get_pps_current(FSC_U8 port)
	{
		return 0;
	}

	FSC_BOOL platform_get_vbus_lvl_enable(FSC_U8 port, VBUS_LVL level)
	{
		//     GPIO_PinState state = GPIO_PIN_RESET;
		//
		//     /* Additional VBUS levels can be added here as needed. */
		//     switch (level) {
		//     case VBUS_LVL_5V:
		//         /* Return the state of the 5V VBUS Source. */
		//         state = HAL_GPIO_ReadPin( VBUS_PORT, VBUS_5V_PIN );
		//
		//         break;
		//     case VBUS_LVL_HV:
		//         /* Return the state of the HV VBUS Source. */
		//         state = HAL_GPIO_ReadPin( VBUS_PORT, VBUS_HV_PIN );
		//
		//         break;
		//     default:
		//         /* Otherwise, return FALSE. */
		//         break;
		//     }
		//
		//     return (state == GPIO_PIN_SET) ? TRUE : FALSE;
	}

	void platform_set_vbus_discharge(FSC_U8 port, FSC_BOOL enable)
	{
		//     /**
		//      *  Enable/Disable the discharge path
		//      * @todo - Implement as needed on platforms that support this feature.
		//      */
		//     HAL_GPIO_WritePin( VBUS_PORT, VBUS_DISC_PIN,
		//                        (enable == TRUE) ? GPIO_PIN_SET : GPIO_PIN_RESET );
	}

	FSC_BOOL platform_get_device_irq_state(FSC_U8 port)
	{
		/**
		* Return the state of the device interrupt signal.
		* Port A, GPIO_PIN_1 -- ACTIVE LOW!
		*/
		#ifdef FSC_POLLING_MODE
			return TRUE;
		#else
			return digitalRead(PIN_fusb_intn) ? FALSE : TRUE;
		#endif /* FSC_POLLING MODE */

		// #ifdef FSC_POLLING_MODE
		//     return TRUE;
		// #else
		//     return HAL_GPIO_ReadPin(INT_N_PORT, INT_N_PIN) ? FALSE : TRUE;
		// #endif /* FSC_POLLING MODE */
	}


	/*******************************************************************************
	 * i2c device object
	 ******************************************************************************/
	//I2C_HandleTypeDef I2cHandle;

	static inline void fusb_i2c_flush()
	{
		while(Wire.available())
		{
			Wire.read();
		}
	}

	FSC_BOOL platform_i2c_write(FSC_U8 SlaveAddress,
								FSC_U8 RegAddrLength,
								FSC_U8 DataLength,
								FSC_U8 PacketSize,
								FSC_U8 IncSize,
								FSC_U32 RegisterAddress,
								FSC_U8* Data)
	{
	// RegAddrLength == 1 always
	// PacketSize == DataLength always
	// IncSize == 1 always
				
	// 7 bit address
	uint8_t DevAddr = (SlaveAddress >> 1);
	
	Wire.beginTransmission((uint8_t)(DevAddr));		//	I2C_WriteByte(I2C_ADDR | I2C_WRITE);
	Wire.write((uint8_t)(RegisterAddress));			//  I2C_WriteByte(RegAddr);
	
	do
	{
		Wire.write(*Data);
		Data++;
	}
	while(--DataLength);

	int result = Wire.endTransmission();		//  I2C_Stop();		
	
	//  0 : Success
	//  1 : Data too long
	//  2 : NACK on transmit of address
	//  3 : NACK on transmit of data
	//  4 : Other error
	
	if(result == 0)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
	
					
	// 		HAL_StatusTypeDef result = HAL_OK;
	// 
	// 		result = HAL_I2C_Mem_Write(&I2cHandle, SlaveAddress, RegisterAddress,
	// 								   RegAddrLength, Data, DataLength,
	// 								   I2C1_TIMEOUT_MAX);
	//		return ((result == HAL_OK) ? TRUE : FALSE);
	}
	
	
	// verified to give correct results for single byte reads
	FSC_BOOL platform_i2c_read( FSC_U8 SlaveAddress,
								FSC_U8 RegAddrLength,
								FSC_U8 DataLength,
								FSC_U8 PacketSize,
								FSC_U8 IncSize,
								FSC_U32 RegisterAddress,
								FSC_U8* Data)
	{
		// RegAddrLength == 1 always
		// PacketSize == DataLength always
		// IncSize == 1 always
		
		// 7 bit address
		uint8_t DevAddr = (SlaveAddress >> 1);

		fusb_i2c_flush(); //?Needed?

		Wire.beginTransmission(DevAddr);	//	I2C_WriteByte(I2C_ADDR | I2C_WRITE);
		Wire.write(RegisterAddress);		//  I2C_WriteByte(RegAddr);
		Wire.endTransmission(false);		//	I2C_Restart();

		Wire.requestFrom((int)DevAddr, (int)DataLength);
		while(Wire.available())
		{
			*Data = Wire.read();
			Data++;
		}
		
		return TRUE;

	// 		HAL_StatusTypeDef result = HAL_OK;
	// 
	// 		result = HAL_I2C_Mem_Read(&I2cHandle, SlaveAddress, RegisterAddress,
	// 								  RegAddrLength, Data, DataLength,
	// 								  I2C1_TIMEOUT_MAX);
	// 
	// 		return ((result == HAL_OK) ? TRUE : FALSE);
	}
}


