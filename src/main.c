#include <lib/cerebellum/gpio.h>
#include <lib/cerebellum/chassis.h>
#include <lib/cerebellum/stepper.h>
#include <util/delay.h>
#include <arch/antares.h>
#include <lib/tmgr.h>
#include <lib/printk.h>

#include <robot/servo.h>
#include <robot/elevator.h>
#include <robot/cannon.h>
#include <robot/odetect.h>
#include <robot/uart.h>
#include <robot/timer.h>

#include "command_parser.h"
#include "cmd_handlers.h"

#include <stdio.h>

#include "usb/usb.h"

#define mmToTicks(mm) ((motor_path_t) (((motor_path_t) (mm) * 480) / 22))
#define ODETECT_FULLFRONT (ODETECT_FRONT | ODETECT_FRIGHT | ODETECT_FLEFT)

/**
 * Enable stepper motor driver
 */
ANTARES_INIT_HIGH(init_stepper)
{
        stepper_enable();
}

ANTARES_INIT_HIGH(servo_pos)
{
        servo_write(1, 20);
        servo_write(2, 80);
        servo_write(3, 40);
        servo_write(4, 60);
}
