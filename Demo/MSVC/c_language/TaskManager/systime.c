#include "systime.h"


uint32_t systick = 0;

#ifdef WIN_MSVC
uint32_t start_time = 0;
#endif

// get_systick() 在不同环境下的实现
uint32_t get_systick()
{
    #ifdef WIN_MSVC
        SYSTEMTIME sys;
        GetLocalTime(&sys);
        if (start_time==0)
			start_time = (sys.wMinute * 60) + (sys.wSecond);
        return (sys.wMinute * 60) + (sys.wSecond) - start_time;
    #endif
    #ifdef ARM_KILL
        return systick;
    #endif
}

uint32_t get_systime()
{
    return get_systick()*SYS_CYCLE_TIME;
}

void update_systime(void)
{
    systick = systick+1;
}