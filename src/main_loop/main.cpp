//============================================================================
// Name        : main.cpp(hex_clock_app)
// Author      : YeongDong Son
// Version     : 1.0
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "main.h"
#include "clock_loop.h"
#include "display_loop.h"

//---------------------------------------------------------------------------
void version_info_print(void)
{
	SYS_LOG("---------hex_clock_app_version---------\n");
	SYS_LOG("Version : %d.%d.%d.%d\n", VER_HIGH_NUMBER, VER_MIDDLE_NUMBER, VER_LOW_NUMBER, VER_HIDDEN_NUMBER);
	SYS_LOG("Version date : %s\n", VER_DATE);
	SYS_LOG("Build date : %s / %s\n", __DATE__,__TIME__);
	SYS_LOG("-------------------------------------\n\n");
}

//---------------------------------------------------------------------------
int init_module(clock_data **c_data)
{
	clock_data *tmp;
	tmp = (clock_data*)malloc(sizeof(clock_data));
    
    memset(&tmp->c_time, 0, sizeof(clock_time));
#ifdef DEBUG_MODE_ENABLE
    tmp->c_time.c_hour = 11;
    tmp->c_time.c_minute = 5;
    tmp->c_time.c_second = 0;
#endif

    tmp->c_gui.clock_frame_buf = (uint32_t *)malloc(DISPLAY_BUF_RGB888);
    memset(tmp->c_gui.clock_frame_buf, 255, DISPLAY_BUF_RGB888);

    display_analog_location_cal(CIRCLE_REDIUS-5, OLP_X-15, OLP_Y+15, &tmp->c_gui.c_location[C_LOCATION_A]);
    display_analog_location_cal(CIRCLE_REDIUS-50, OLP_X, OLP_Y, &tmp->c_gui.c_location[C_LOCATION_B]);
    display_analog_location_cal(CIRCLE_REDIUS-70, OLP_X, OLP_Y, &tmp->c_gui.c_location[C_LOCATION_HOUR]);
    display_analog_location_cal(CIRCLE_REDIUS-100, OLP_X, OLP_Y, &tmp->c_gui.c_location[C_LOCATION_MIN]);
    display_analog_location_cal(CIRCLE_REDIUS-130, OLP_X, OLP_Y, &tmp->c_gui.c_location[C_LOCATION_SEC]);

    *c_data = tmp;

    return SUCCESS;
}

//---------------------------------------------------------------------------
int run_module(clock_data *c_data)
{
    SYS_LOG("start hex_clock_app!!\n");
    char window_name[] = WINDOW_NAME;

    while(1)
    {
        clock_cal(&c_data->c_time);
        display_create_or_refresh(window_name, FIX_WIDTH, FIX_HEIGHT, CIRCLE_REDIUS, OLP_X, OLP_Y, c_data);

        usleep(1000 * TIME_DELAY);
    }

    return SUCCESS;
}

//---------------------------------------------------------------------------
int close_module(clock_data *c_data)
{
    char window_name[] = WINDOW_NAME;

    free(c_data->c_gui.clock_frame_buf);
    display_destroy(window_name);

    return SUCCESS;
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
int main(void)
{
    int reture_value;
    clock_data *c_ctx;

    version_info_print();

    reture_value = init_module(&c_ctx);
    if(reture_value < SUCCESS){ERR_LOG("init_module ecode : %d", reture_value); return reture_value;}
    reture_value = run_module(c_ctx);
    if(reture_value < SUCCESS){ERR_LOG("run_module ecode : %d", reture_value); return reture_value;}
    reture_value = close_module(c_ctx);
    if(reture_value < SUCCESS){ERR_LOG("run_module ecode : %d", reture_value); return reture_value;}

    return SUCCESS;
}