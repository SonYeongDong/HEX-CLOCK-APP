#ifndef _DISPLAY_LOOP_H
#define _DISPLAY_LOOP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>              //file open
#include <vector>
#include <math.h>

// opencv lib
#include <iostream>
#include "opencv.hpp"
#include "core.hpp"
#include "highgui.hpp"
#include "imgproc.hpp"
#include "ocl.hpp"
#include "imgcodecs.hpp"

#include "user_def.h"

using namespace std;
using namespace cv;

int display_analog_location_cal(uint16_t radius, uint16_t olp_x, uint16_t olp_y,  clock_location *c_location);

int display_create_or_refresh(char *window_name, uint16_t display_width, uint16_t display_height, uint16_t radius, uint16_t olp_x, uint16_t olp_y, clock_data *c_data);
int draw_background(cv::Mat &frame_buf, uint16_t display_width, uint16_t display_height);

int draw_analog_clock(cv::Mat &frame_buf, uint16_t display_width, uint16_t display_height, uint16_t radius, uint16_t olp_x, uint16_t olp_y, clock_data *c_data);
int draw_clock_number(cv::Mat &frame_buf, clock_location *c_location);
int draw_clock_line(cv::Mat &frame_buf, clock_location *c_location);
int draw_clock_hour_min_sec(cv::Mat &frame_buf, uint16_t olp_x, uint16_t olp_y, clock_time *c_time, clock_location *c_hour, clock_location *c_min, clock_location *c_sec);

int draw_digital_clock(cv::Mat &frame_buf, uint16_t display_width, uint16_t display_height, clock_time *c_time);
int draw_work_list(cv::Mat &frame_buf, uint16_t display_width, uint16_t display_height);
int display_show(cv::Mat &frame_buf, char *window_name, uint16_t display_width, uint16_t display_height);

int display_destroy(char *window_name);
#endif