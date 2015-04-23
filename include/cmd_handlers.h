#ifndef INCLUDE_CMD_HANDLERS_H
#define INCLUDE_CMD_HANDLERS_H

#include <stdio.h>
#include <arch/antares.h>

/**
 * Default handlers for Cerebellum subsystems
 */

/**
 * @addgroup Chassis subsystem
 * @{
 */

#include <lib/cerebellum/chassis.h>

struct chassis_twist {
        int16_t left;
        int16_t right;
        int32_t path;
};

struct chassis_dynamics {
        int16_t acc_num;
        int16_t acc_den;

        int16_t brake_num;
        int16_t brake_denom;
};

void *chassis_twist_handler(char method, void *data, uint8_t *size);
void *chassis_dynamics_handler(char method, void *data, uint8_t *size);
void *chassis_state_handler(char method, void *data, uint8_t *size);

/**
 * @}
 */

/**
 * @addgroup Servo subsystem
 * @{
 */

#include <robot/servo.h>
void *servo_handler(char method, void *data, uint8_t *size);

/**
 * @}
 */

#include <lib/cerebellum/gpio.h>
void *led_handler(char method, void *data, uint8_t *out_size);
void *bsensor_handler(char method, void *data, uint8_t *size);

#include <robot/odetect.h>
void *odetect_handler(char method, void *data, uint8_t *size);

#endif
