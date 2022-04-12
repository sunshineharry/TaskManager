#include "systime.h"


uint32_t systime = 0;

#ifdef WIN_MSVC
uint32_t start_time = 0;
#endif

// get_systime() 在不同环境下的实现
uint32_t get_systime()
{
    #ifdef WIN_MSVC
        SYSTEMTIME sys;
        GetLocalTime(&sys);
        if (start_time==0)
			start_time = (sys.wMinute * 60) + (sys.wSecond);
        return (sys.wMinute * 60) + (sys.wSecond) - start_time;
    #endif
    #ifdef ARM_KILL
        return systime;
    #endif
    }


void update_systime(void)
{
    systime = systime+1;
}