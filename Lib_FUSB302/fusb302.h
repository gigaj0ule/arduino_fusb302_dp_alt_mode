/*
 * IncFile1.h
 *
 * Created: 8/16/2018 9:43:15 PM
 *  Author: root
 */ 


#ifndef FUSB302_H_
#define FUSB302_H_

#include <stdbool.h>

class FUSB302_
{
	public:
	FUSB302_(void);
	void begin(int intn_pin);
	void loop(void);
	void displayPort_configure(bool hpd_state);
	bool pd_contract_good;
	
	private:
	int pin_fusb_intn;
	long timer_value;
};

extern FUSB302_ FUSB302;

void intCallback(void);

// #ifdef FSC_HAVE_DP
// FSC_BOOL platform_dp_enable_pins(FSC_BOOL enable, FSC_U32 config);
// void platform_dp_status_update(FSC_U32 status);
// #endif /* FSC_HAVE_DP */


#endif /* FUSB302_H_ */