//============================================================================
// Name        : clock_loop.cpp(hex_clock_app)
// Author      : YeongDong Son
// Version     : 1.0
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "clock_loop.h"

//---------------------------------------------------------------------------
int read_system_time(clock_time *c_time)
{
    struct timespec specific_time;
    struct tm *now;
    int millsec;

    clock_gettime(CLOCK_REALTIME, &specific_time);
    now = localtime(&specific_time.tv_sec);

    millsec = floor(specific_time.tv_nsec/1.0e6);

    c_time->c_year = (uint16_t)(1900 + now->tm_year);
    c_time->c_month = (uint8_t)(now->tm_mon + 1);
    c_time->c_day = (uint8_t)now->tm_mday;

    c_time->c_hour = (uint8_t)now->tm_hour;
    c_time->c_minute = (uint8_t)now->tm_min;
    c_time->c_second = (uint8_t)now->tm_sec;
    c_time->c_millsec = (uint16_t)millsec;

    // DBG_LOG("%04d-%02d-%02d %02d:%02d:%02d.%03d\n", 
    //         1900 + now->tm_year, now->tm_mon + 1, 
    //         now->tm_mday, now->tm_hour, 
    //         now->tm_min, now->tm_sec, millsec);

    return SUCCESS;
}

//---------------------------------------------------------------------------
int clock_cal(clock_time *c_time)
{
#ifndef DEBUG_MODE_ENABLE
    read_system_time(c_time);
#else
    c_time->c_year = (uint16_t)2001;
    c_time->c_month = (uint8_t)2;
    c_time->c_day = (uint8_t)27;

    c_time->c_millsec+=444;
    if(c_time->c_millsec >= 1000)
    {
        c_time->c_millsec = 0;
        c_time->c_second+=1;
        if(c_time->c_second >= SLS)
        {
            c_time->c_second = 0;
            c_time->c_minute+=1;
            if(c_time->c_minute >= MLS)
            {
                c_time->c_minute = 0;
                c_time->c_hour+=1;
                if(c_time->c_hour >= HLS+HLS)
                    c_time->c_hour = 0;
            }
        }
    }
#endif

    return SUCCESS;
}