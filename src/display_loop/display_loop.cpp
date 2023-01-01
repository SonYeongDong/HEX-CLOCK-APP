//============================================================================
// Name        : display_loop.cpp(hex_clock_app)
// Author      : YeongDong Son
// Version     : 1.0
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "display_loop.h"

//---------------------------------------------------------------------------
int display_analog_location_cal(uint16_t radius, uint16_t olp_x, uint16_t olp_y, clock_location *c_location)
{
    const double PI = 3.1415926;
    double x_location, y_location;
    int write_index_cw = 1, write_index_ccw = 89, i = 0;
    int hour_index = 0, minute_index = 0, second_index = 0;

    uint16_t location_raw[5][90][MAX_LOCATION] = {0,};
    //basic location write
    location_raw[1][0][Y_LOCATION] = radius;
    location_raw[2][0][X_LOCATION] = -radius;
    location_raw[3][0][Y_LOCATION] = -radius;
    location_raw[4][0][X_LOCATION] = radius;
    
    for(int c_angle = 89; c_angle >= 1; c_angle--)
    {
        x_location = radius * cos(c_angle * (PI / 180));
        y_location = radius * sin(c_angle * (PI / 180));

        location_raw[1][write_index_cw][X_LOCATION] = (uint16_t)x_location;
        location_raw[1][write_index_cw][Y_LOCATION] = (uint16_t)y_location;

        location_raw[2][write_index_ccw][X_LOCATION] = -location_raw[1][write_index_cw][X_LOCATION];
        location_raw[2][write_index_ccw][Y_LOCATION] = location_raw[1][write_index_cw][Y_LOCATION];

        location_raw[3][write_index_cw][X_LOCATION] = -location_raw[1][write_index_cw][X_LOCATION];
        location_raw[3][write_index_cw][Y_LOCATION] = -location_raw[1][write_index_cw][Y_LOCATION];

        location_raw[4][write_index_ccw][X_LOCATION] = location_raw[1][write_index_cw][X_LOCATION];
        location_raw[4][write_index_ccw][Y_LOCATION] = -location_raw[1][write_index_cw][Y_LOCATION];

        write_index_cw++;
        write_index_ccw--;
    }

    write_index_ccw = 89;
    for(i = 0; i <= 89; i++)
    {
        c_location->clock_full_location[0 + i][X_LOCATION] = location_raw[4][write_index_ccw][X_LOCATION] + olp_x;
        c_location->clock_full_location[0 + i][Y_LOCATION] = location_raw[4][write_index_ccw][Y_LOCATION] + olp_y;
        c_location->clock_full_location[90 + i][X_LOCATION] = location_raw[1][write_index_ccw][X_LOCATION] + olp_x;
        c_location->clock_full_location[90 + i][Y_LOCATION] = location_raw[1][write_index_ccw][Y_LOCATION] + olp_y;
        c_location->clock_full_location[180 + i][X_LOCATION] = location_raw[2][write_index_ccw][X_LOCATION] + olp_x;
        c_location->clock_full_location[180 + i][Y_LOCATION] = location_raw[2][write_index_ccw][Y_LOCATION] + olp_y;
        c_location->clock_full_location[270 + i][X_LOCATION] = location_raw[3][write_index_ccw][X_LOCATION] + olp_x;
        c_location->clock_full_location[270 + i][Y_LOCATION] = location_raw[3][write_index_ccw][Y_LOCATION] + olp_y;
   
        write_index_ccw--;
    }

    for(i = 0; i < HLS; i++)
    {
        c_location->hour_location[i][X_LOCATION] = c_location->clock_full_location[hour_index][X_LOCATION];
        c_location->hour_location[i][Y_LOCATION] = c_location->clock_full_location[hour_index][Y_LOCATION];
        hour_index += CFLS / HLS;
    }
    for(i = 0; i < MLS; i++)
    {
        c_location->minute_location[i][X_LOCATION] = c_location->clock_full_location[minute_index][X_LOCATION];
        c_location->minute_location[i][Y_LOCATION] = c_location->clock_full_location[minute_index][Y_LOCATION];
        minute_index += CFLS / MLS;
    }
    for(i = 0; i < SLS; i++)
    {
        c_location->second_location[i][X_LOCATION] = c_location->clock_full_location[second_index][X_LOCATION];
        c_location->second_location[i][Y_LOCATION] = c_location->clock_full_location[second_index][Y_LOCATION];
        second_index += CFLS / SLS;
    }

    // for(i = 0; i <= 359; i++)
    // {
    //     DBG_LOG("angle %03d : [%03d, %03d]\n", i, c_location->clock_full_location[i][X_LOCATION], c_location->clock_full_location[i][Y_LOCATION]);
    // }

    return SUCCESS;
}

//---------------------------------------------------------------------------
int display_create_or_refresh(char *window_name, uint16_t display_width, uint16_t display_height, uint16_t radius, uint16_t olp_x, uint16_t olp_y, clock_data *c_data)
{
    Mat frame_buf(display_height, display_width, CV_8UC3, c_data->c_gui.clock_frame_buf);

    draw_background(std::ref(frame_buf), display_width, display_height);
    draw_analog_clock(std::ref(frame_buf), display_width, display_height, radius, olp_x, olp_y, c_data);
    draw_digital_clock(std::ref(frame_buf), display_width, display_height, &c_data->c_time);
    draw_work_list(std::ref(frame_buf), display_width, display_height);
    display_show(std::ref(frame_buf), window_name, display_width, display_height);

    return SUCCESS;
}
int draw_background(cv::Mat &frame_buf, uint16_t display_width, uint16_t display_height)
{
    char temp_string[20] = {0,};
    rectangle(frame_buf, Point(0, 0), Point(1280, 720), Scalar(255, 255, 255), CV_FILLED, 8, 0);
    sprintf(temp_string, "VERSION-%d.%d.%d.%d", VER_HIGH_NUMBER, VER_MIDDLE_NUMBER, VER_LOW_NUMBER, VER_HIDDEN_NUMBER);

    putText(frame_buf, "HEX CLOCK APP", Point(20, 60), 1, 3.5, Scalar(0, 0, 0), THICKNESS_FONT_BACKGROUNT, 16, 0);
    putText(frame_buf, "HEX CLOCK APP", Point(20, 60), 1, 3.5, Scalar(180, 224, 197), THICKNESS_FONT, 16, 0);
    putText(frame_buf, temp_string, Point(1070, 35), 1, 1.4, Scalar(0, 0, 0), THICKNESS_FONT_BACKGROUNT-3, 16, 0);
    putText(frame_buf, temp_string, Point(1070, 35), 1, 1.4, Scalar(180, 224, 197), THICKNESS_FONT-2, 16, 0);
    putText(frame_buf, "MADE BY SYD", Point(1105, 60), 1, 1.4, Scalar(0, 0, 0), THICKNESS_FONT_BACKGROUNT-3, 16, 0);
    putText(frame_buf, "MADE BY SYD", Point(1105, 60), 1, 1.4, Scalar(180, 224, 197), THICKNESS_FONT-2, 16, 0);

    rectangle(frame_buf, Point(20, 80), Point(1260, 700), Scalar(0, 0, 0), THICKNESS, 8, 0);
    
    return SUCCESS;
}
int draw_analog_clock(cv::Mat &frame_buf, uint16_t display_width, uint16_t display_height, uint16_t radius, uint16_t olp_x, uint16_t olp_y, clock_data *c_data)
{
    rectangle(frame_buf, Point(20, 80), Point(640, 700), Scalar(166, 166, 166), CV_FILLED, 8, 0);
    rectangle(frame_buf, Point(20, 80), Point(640, 700), Scalar(0, 0, 0), THICKNESS, 8, 0);

    circle(frame_buf, Point(olp_x, olp_y), radius+50, Scalar(89, 89, 89), CV_FILLED, 16, 0);
    circle(frame_buf, Point(olp_x, olp_y), radius+50, Scalar(0, 0, 0), THICKNESS, 16, 0);
    circle(frame_buf, Point(olp_x, olp_y), radius+30, Scalar(217, 217, 217), CV_FILLED, 16, 0);
    circle(frame_buf, Point(olp_x, olp_y), radius+30, Scalar(0, 0, 0), THICKNESS, 16, 0);

    //clock number draw
    draw_clock_number(std::ref(frame_buf), &c_data->c_gui.c_location[C_LOCATION_A]);

    //clock line draw
    draw_clock_line(std::ref(frame_buf), &c_data->c_gui.c_location[C_LOCATION_B]);

    //clock hour, minute, second draw
    draw_clock_hour_min_sec(std::ref(frame_buf), olp_x, olp_y, &c_data->c_time, 
                            &c_data->c_gui.c_location[C_LOCATION_HOUR], 
                            &c_data->c_gui.c_location[C_LOCATION_MIN], 
                            &c_data->c_gui.c_location[C_LOCATION_SEC]);

    circle(frame_buf, Point(olp_x, olp_y), radius-230, Scalar(89, 89, 89), CV_FILLED, 16, 0);
    circle(frame_buf, Point(olp_x, olp_y), radius-230, Scalar(0, 0, 0), THICKNESS, 16, 0);

    return SUCCESS;
}
int draw_clock_number(cv::Mat &frame_buf, clock_location *c_location)
{
    int i;
    char temp_string[5] = {0,};

    for(i = 0; i < HLS; i++)
    {
        if(i == 0)
            sprintf(temp_string, "%X", 12);
        else
            sprintf(temp_string, "%X", i);
        
        putText(frame_buf, temp_string, Point(c_location->hour_location[i][X_LOCATION], c_location->hour_location[i][Y_LOCATION]), 1, 3, Scalar(0, 0, 0), THICKNESS_FONT_BACKGROUNT, 16, 0);
        putText(frame_buf, temp_string, Point(c_location->hour_location[i][X_LOCATION], c_location->hour_location[i][Y_LOCATION]), 1, 3, Scalar(180, 224, 197), THICKNESS_FONT, 16, 0);
    }

    return SUCCESS;
}

int draw_clock_line(cv::Mat &frame_buf, clock_location *c_location)
{
    int i;

    for(i = 0; i < MLS; i++)
    {
        line(frame_buf, Point(c_location->minute_location[i][X_LOCATION], c_location->minute_location[i][Y_LOCATION]), 
                        Point(c_location->minute_location[i][X_LOCATION], c_location->minute_location[i][Y_LOCATION]), Scalar(0,0,0), THICKNESS+3, 16, 0);
        line(frame_buf, Point(c_location->minute_location[i][X_LOCATION], c_location->minute_location[i][Y_LOCATION]), 
                        Point(c_location->minute_location[i][X_LOCATION], c_location->minute_location[i][Y_LOCATION]), Scalar(100,100,200), THICKNESS, 16, 0);
    }
    for(i = 0; i < HLS; i++)
    {
        line(frame_buf, Point(c_location->hour_location[i][X_LOCATION], c_location->hour_location[i][Y_LOCATION]), 
                        Point(c_location->hour_location[i][X_LOCATION], c_location->hour_location[i][Y_LOCATION]), Scalar(0,0,0), THICKNESS_FONT_BACKGROUNT+5, 16, 0);
        line(frame_buf, Point(c_location->hour_location[i][X_LOCATION], c_location->hour_location[i][Y_LOCATION]), 
                        Point(c_location->hour_location[i][X_LOCATION], c_location->hour_location[i][Y_LOCATION]), Scalar(200,100,100), THICKNESS_FONT_BACKGROUNT, 16, 0);
    }

    return SUCCESS;
}

int draw_clock_hour_min_sec(cv::Mat &frame_buf, uint16_t olp_x, uint16_t olp_y, clock_time *c_time, clock_location *c_hour, clock_location *c_min, clock_location *c_sec)
{
    //hour
    uint16_t hour_am_pm_fix;
    if(c_time->c_hour >= HLS)
        hour_am_pm_fix = c_time->c_hour-HLS;
    else
        hour_am_pm_fix = c_time->c_hour;

    line(frame_buf, Point(olp_x, olp_y), Point(c_hour->hour_location[hour_am_pm_fix][X_LOCATION], c_hour->hour_location[hour_am_pm_fix][Y_LOCATION]), 
         Scalar(0,0,0), THICKNESS_FONT_BACKGROUNT+1, 16, 0);
    line(frame_buf, Point(olp_x, olp_y), Point(c_hour->hour_location[hour_am_pm_fix][X_LOCATION], c_hour->hour_location[hour_am_pm_fix][Y_LOCATION]), 
         Scalar(0,163,214), THICKNESS_FONT_BACKGROUNT-4, 16, 0);

    //minute
    line(frame_buf, Point(olp_x, olp_y), Point(c_min->minute_location[c_time->c_minute][X_LOCATION], c_min->minute_location[c_time->c_minute][Y_LOCATION]), 
         Scalar(0,0,0), THICKNESS_FONT_BACKGROUNT+3, 16, 0);
    line(frame_buf, Point(olp_x, olp_y), Point(c_min->minute_location[c_time->c_minute][X_LOCATION], c_min->minute_location[c_time->c_minute][Y_LOCATION]), 
         Scalar(200,100,100), THICKNESS_FONT_BACKGROUNT-2, 16, 0);

    //second
    line(frame_buf, Point(olp_x, olp_y), Point(c_sec->second_location[c_time->c_second][X_LOCATION], c_sec->second_location[c_time->c_second][Y_LOCATION]), 
         Scalar(0,0,0), THICKNESS_FONT_BACKGROUNT+5, 16, 0);
    line(frame_buf, Point(olp_x, olp_y), Point(c_sec->second_location[c_time->c_second][X_LOCATION], c_sec->second_location[c_time->c_second][Y_LOCATION]), 
         Scalar(155,155,255), THICKNESS_FONT_BACKGROUNT, 16, 0);

    return SUCCESS;
}

int draw_digital_clock(cv::Mat &frame_buf, uint16_t display_width, uint16_t display_height, clock_time *c_time)
{
    char data_temp_string[20] = {0,};
    char time_temp_string[20] = {0,};
    sprintf(data_temp_string, "%04X-%02X-%02X-KOR", c_time->c_year, c_time->c_month, c_time->c_day);
    sprintf(time_temp_string, "%02X:%02X:%02X.%03X", c_time->c_hour, c_time->c_minute, c_time->c_second, c_time->c_millsec);
    
    rectangle(frame_buf, Point(640, 80), Point(1260, 260), Scalar(204, 242, 255), CV_FILLED, 8, 0);
    rectangle(frame_buf, Point(640, 80), Point(1260, 260), Scalar(0, 0, 0), THICKNESS, 8, 0);

    //date
    putText(frame_buf, data_temp_string, Point(660, 150), 1, 4, Scalar(0, 0, 0), THICKNESS_FONT_BACKGROUNT, 16, 0);
    putText(frame_buf, data_temp_string, Point(660, 150), 1, 4, Scalar(155,155,255), THICKNESS_FONT, 16, 0);

    //time
    putText(frame_buf, time_temp_string, Point(665, 240), 1, 5.5, Scalar(0, 0, 0), THICKNESS_FONT_BACKGROUNT, 16, 0);
    putText(frame_buf, time_temp_string, Point(665, 240), 1, 5.5, Scalar(155,155,255), THICKNESS_FONT, 16, 0);
    
    return SUCCESS;
}
int draw_work_list(cv::Mat &frame_buf, uint16_t display_width, uint16_t display_height)
{
    //demo write
    rectangle(frame_buf, Point(640, 260), Point(1260, 700), Scalar(217, 217, 217), CV_FILLED, 8, 0);
    rectangle(frame_buf, Point(640, 260), Point(1260, 700), Scalar(0, 0, 0), THICKNESS, 8, 0);

    putText(frame_buf, "TODAY WORK LIST", Point(700, 320), 1, 3.5, Scalar(0, 0, 0), THICKNESS_FONT_BACKGROUNT, 16, 0);
    putText(frame_buf, "TODAY WORK LIST", Point(700, 320), 1, 3.5, Scalar(238, 215, 189), THICKNESS_FONT, 16, 0);

    rectangle(frame_buf, Point(650, 340), Point(1250, 690), Scalar(217, 240, 226), CV_FILLED, 8, 0);
    rectangle(frame_buf, Point(650, 340), Point(1250, 690), Scalar(0, 0, 0), THICKNESS, 8, 0);

    line(frame_buf, Point(665, 390), Point(1235, 390), Scalar(89, 89, 89), THICKNESS_FONT, 16, 0);
    line(frame_buf, Point(665, 440), Point(1235, 440), Scalar(89, 89, 89), THICKNESS_FONT, 16, 0);
    
    line(frame_buf, Point(665, 540), Point(1235, 540), Scalar(89, 89, 89), THICKNESS_FONT, 16, 0);
    line(frame_buf, Point(665, 590), Point(1235, 590), Scalar(89, 89, 89), THICKNESS_FONT, 16, 0);
    line(frame_buf, Point(665, 640), Point(1235, 640), Scalar(89, 89, 89), THICKNESS_FONT, 16, 0);

#ifndef DEBUG_MODE_ENABLE
    putText(frame_buf, "NOTHING!", Point(715, 525), 1, 6.5, Scalar(0, 0, 0), THICKNESS_FONT_BACKGROUNT+7, 16, 0);
    putText(frame_buf, "NOTHING!", Point(715, 525), 1, 6.5, Scalar(0, 0, 255), THICKNESS_FONT+6, 16, 0);
 #else
    line(frame_buf, Point(665, 490), Point(1235, 490), Scalar(89, 89, 89), THICKNESS_FONT, 16, 0);
    putText(frame_buf, "07d1-01-1B is the", Point(670, 380), 1, 2.5, Scalar(0, 0, 0), THICKNESS_FONT_BACKGROUNT-2, 16, 0);
    putText(frame_buf, "07d1-01-1B is the", Point(670, 380), 1, 2.5, Scalar(180, 180, 180), THICKNESS_FONT-2, 16, 0);
    putText(frame_buf, "birth day of syd", Point(670, 430), 1, 2.5, Scalar(0, 0, 0), THICKNESS_FONT_BACKGROUNT-2, 16, 0);
    putText(frame_buf, "birth day of syd", Point(670, 430), 1, 2.5, Scalar(180, 180, 180), THICKNESS_FONT-2, 16, 0); 
    putText(frame_buf, "embedded sw developer", Point(670, 480), 1, 2.5, Scalar(0, 0, 0), THICKNESS_FONT_BACKGROUNT-2, 16, 0);
    putText(frame_buf, "embedded sw developer", Point(670, 480), 1, 2.5, Scalar(180, 180, 180), THICKNESS_FONT-2, 16, 0); 
 #endif

    return SUCCESS;
}
int display_show(cv::Mat &frame_buf, char *window_name, uint16_t display_width, uint16_t display_height)
{
    int y, x;
    for(y = 0; y <= display_height; y++)
    {
        for(x = 0; x <= display_width*3; x+=3)
        {
           if((uint8_t)frame_buf.at<uint8_t>(y,x) >= BLUE_REDUCT)
                frame_buf.at<uint8_t>(y,x) = (uint8_t)frame_buf.at<uint8_t>(y,x) - BLUE_REDUCT;
        }
    }

    namedWindow(window_name, CV_WINDOW_NORMAL);
    resizeWindow(window_name, display_width, display_height);
    imshow(window_name, frame_buf);
    waitKey(33);

    return SUCCESS;
}

//---------------------------------------------------------------------------
int display_destroy(char *window_name)
{
    destroyWindow(window_name);
    return SUCCESS;
}