#ifndef INCLUDE_ROBOT_EXTRA_H
#define INCLUDE_ROBOT_EXTRA_H

#include <robot/servo.h>
#include <lib/tmgr.h>

#include "cmd_handlers.h"

#define BSENSOR_RIGHT 0
#define BSENSOR_LEFT 1
#define BSENSOR_SHMORGALKA 2
#define BSENSOR_SELECTOR 3

#define OD_FRONT 1
#define OD_REAR 2
#define OD_RIGHT 4
#define OD_LEFT 8
#define OD_FLEFT 16
#define OD_FRIGHT 32

#define OD_FULLFRONT (OD_FRONT | OD_FLEFT | OD_FRIGHT)
#define OD_SIDES (OD_LEFT | OD_RIGHT)
#define OD_ALL 63

#define ROBOT_RADIUS 293 / 2

#define mmToTicks(a) ((a) * 480 / 22)
#define mmsToTicks(a) ((a) * 67)

void catch_stand_open();
void catch_stand_close();

void elevator_middle();
void elevator_up();
void elevator_up_steady();
void elevator_down();

void paw_open();
void paw_close();
void ball_holder_open();
void ball_holder_close();

static struct chassis_dynamics dyns;

uint8_t bsensor_get(uint8_t index);

void twist(int16_t spd_left, int16_t spd_right, int32_t distance);
void twist_block(int16_t spd_left, int16_t spd_right, int32_t distance);
uint8_t twist_busy();
void twist_rotate(int16_t speed, int16_t angle);
void twist_rotate_block(int16_t speed, int16_t angle);
void dynamics(int16_t acc_num, int16_t acc_den, int16_t brake_num, int16_t brake_den);

#endif
