#ifndef _MAIN_H
#define _MAIN_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#include "user_def.h"

void version_info_print(void);
int init_module(clock_data **c_data);
int run_module(clock_data *c_data);
int close_module(clock_data *c_data);

#endif