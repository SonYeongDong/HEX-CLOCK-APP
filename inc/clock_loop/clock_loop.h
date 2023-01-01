#ifndef _CLOCK_LOOP_H
#define _CLOCK_LOOP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include <math.h>
#include <unistd.h>

#include "user_def.h"

int clock_cal(clock_time *c_time);
int read_system_time(clock_time *c_time);

#endif