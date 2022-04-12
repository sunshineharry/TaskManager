#include "systime.h"
#include "stm32f10x_conf.h"

uint32_t systime = 0;

#ifdef _MSC_VER

uint32_t get_systime()
{
	SYSTEMTIME sys;
	GetLocalTime(&sys);
	static uint32_t thistime = (sys.wMinute * 60) + (sys.wSecond);
	return (sys.wMinute * 60) + (sys.wSecond) - thistime;
}
#else

void update_systime(void)
{
    systime = systime+1;
}

uint32_t get_systime()
{
    return systime;
}
#endif