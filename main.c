#include <stdint.h>
#include <stdbool.h>
#include "system.h"
#include "speaker.h"

#define TIME_20_SEC										20000

static sysTimer_t speakerTimer;

int main(void)
{
	System_Init();
	Speaker_Init();
	
	System_TimerInit(&speakerTimer, TIME_20_SEC);
	
	
	while(1)
	{
		Speaker_Activate(SPEAKER_FREQ_10KHZ, SPEAKER_DUTY_CYCLE_90PERCENT);
		if(System_TimerDoneCounting(&speakerTimer))
		{
			Speaker_Deactivate();
		}
		System_Timer_DelayMs(2000);
	}
}
