#ifndef _USER_DEF_H
#define _USER_DEF_H

#include <stdio.h>
#include <stdint.h>

//-------------------APP_Version-----------------------------
#define VER_HIGH_NUMBER                 0
#define VER_MIDDLE_NUMBER               0
#define VER_LOW_NUMBER                  1
#define VER_HIDDEN_NUMBER               0
#define VER_DATE                        "20221231"

//-------------------Select_APP_Mode-------------------------
//#define DEBUG_MODE_ENABLE                             //DEBUG ENABLE/DISABLE(FAST CLOCK MODE)

//--------------------APP_PERFORMANCE-------------------------
#ifndef DEBUG_MODE_ENABLE
    #define TIME_DELAY                       100             //100ms
#else
    #define TIME_DELAY                       1               //1ms
#endif


//--------------------SYSTEM_DEFINE---------------------------
enum
{
    X_LOCATION = 0,
    Y_LOCATION    ,
    
    MAX_LOCATION  ,
};
#define THICKNESS                       4
#define THICKNESS_FONT_BACKGROUNT       10
#define THICKNESS_FONT                  4
#define BLUE_REDUCT                     50                //RGB BLUE REDUCTION

#define CIRCLE_REDIUS                   250               //CLOCK CIRCLE REDIUS               
#define OLP_X                           330               //ORIGIN LOCATION POINT X
#define OLP_Y                           390               //ORIGIN LOCATION POINT Y

#define CFLS                            360               //CLOCK FULL LOCATION SIZE
#define HLS                             12                //HOUR LOCATION SIZE
#define MLS                             60                //MINUTE LOCATION SIZE
#define SLS                             60                //SECOND LOCATION SIZE

#define WINDOW_NAME                     "HEX_CLOCK_APP"   //CREATE OR DESTROY WINDOW NAME 

//--------------------DATA_SIZE-------------------------------
//--DISPLAY_BUFFER_SIZE---
#define FIX_WIDTH                        1280
#define FIX_HEIGHT                       720

//--DISPLAY_BUFFER_SIZE---
#define DISPLAY_BUF_RGB888               FIX_WIDTH*FIX_HEIGHT*24/8 //(WIDTH * HEIGHT * RGB888 / 8bit)

//--C_GUI_SIZE---
enum
{
    C_LOCATION_A     = 0,
    C_LOCATION_B        ,
    C_LOCATION_HOUR     ,
    C_LOCATION_MIN      ,
    C_LOCATION_SEC      ,

    MAX_C_LOCATION_SIZE ,
};

//--------------------DATA_STURUCT----------------------------
typedef struct clock_time
{
    uint16_t c_year;
    uint8_t c_month;
    uint8_t c_day;

    uint8_t c_hour;
    uint8_t c_minute;
    uint8_t c_second;
    uint16_t c_millsec;
}clock_time;

typedef struct clock_location
{
    uint16_t clock_full_location[CFLS][MAX_LOCATION];
    uint16_t hour_location[HLS][MAX_LOCATION];
    uint16_t minute_location[MLS][MAX_LOCATION];
    uint16_t second_location[SLS][MAX_LOCATION];
}clock_location;

typedef struct clock_gui
{
    uint32_t *clock_frame_buf;
    clock_location c_location[MAX_C_LOCATION_SIZE];

}clock_gui;

typedef struct clock_data
{
    clock_time c_time;
    clock_gui c_gui;
}clock_data;

//--------------------SYSTEM_UTILITY_FOR_DEBUG----------------
#define DEBUG_EN                    1 

enum
{
    FAIL_PROGRAM_SHUTDOWN       = -11,
    FAIL_10                          ,
    FAIL_9                           ,
    FAIL_8                           ,
    FAIL_7                           ,
    FAIL_6                           ,
    FAIL_5                           ,
    FAIL_4                           ,
    FAIL_3                           ,
    FAIL_2                           ,
    FAIL_1                           ,
    SUCCESS                          ,
};

#define SYS_LOG(fmt,arg...)	{	printf("[SYS INFO] " fmt,##arg);            }
#define ERR_LOG(fmt,arg...)	{	printf("[ERROR] " fmt,##arg);	            }
#define DBG_LOG(fmt,arg...)	{	if(DEBUG_EN)	printf("[dbg] " fmt,##arg);	}

#endif