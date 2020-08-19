//#############################################################################
// Includes
//-----------------------------------------------------------------------------
#include <Wire.h>

#include "./Lib_FUSB302/fusb302.h"


void setup() {
	
	Wire.begin();

	// Begin power delivery subsystem
	FUSB302.begin(PIN_fusb_intn);

	// Wait until power contract is signed, or break if no response after 1 second
	//uint64_t break_time = millis() + 4000;

	/*
	while(FUSB302.pd_contract_good == false) {
		FUSB302.loop();
		uint32_t now_time = millis();
		digitalWrite(PA1, (now_time % 500 > 450));
		if(now_time >= break_time) {
			break;
			// Uh oh, we're hanging here and not getting a PD contract...
		}
	}*/
};


void loop(){

	// Poll usb pd state
	FUSB302.loop();

	// Status LED
	if(FUSB302.pd_contract_good == true) {
		// Have usb contract

		// Light up LED 
		digitalWrite(PA1, HIGH);
	}
	
	delay(2);
};


// -------------------------------------------------------------------------
void find_i2c_devices()
{
	delay(1000);
	
	volatile uint8_t error, address;
	int nDevices;
	
	SerialUSB.println("Scanning I2C Bus...");
	
	nDevices = 0;
	for(address = 1; address < 127; address++ )
	{
		// The i2c_scanner uses the return value of
		// the Write.endTransmisstion to see if
		// a device did acknowledge to the address.
		while(Wire.available())
		{
			Wire.read();
		}
		
		Wire.beginTransmission(address);
		error = Wire.endTransmission();
		
		if (error == 0)
		{
			digitalWrite(PA1, HIGH);
			delay(100);
			digitalWrite(PA1, LOW);
			delay(100);

			// 34, 44, 56, 74, 
			
			SerialUSB.print("I2C device found at address 0x");
			if (address<16)
			SerialUSB.print("0");
			SerialUSB.print(address,HEX);
			SerialUSB.println("  !");
			
			nDevices++;
		}
		else if (error==4)
		{
			SerialUSB.print("Unknown error at address 0x");
			if (address<16)
			SerialUSB.print("0");
			SerialUSB.println(address,HEX);
		}
	}
	
	if (nDevices == 0)
	{
		SerialUSB.println("No I2C devices found\n");
		digitalWrite(PA1, HIGH);
	}
	else
	{
		SerialUSB.println("Done!\n");
	}
}

