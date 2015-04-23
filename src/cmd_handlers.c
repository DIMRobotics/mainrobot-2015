#include "cmd_handlers.h"

/**
 * @addgroup Chassis handlers
 * @{
 */

static struct chassis_twist _twist;
static struct chassis_dynamics _dynamics;

static uint8_t default_y = 'y';

ANTARES_INIT_LOW(chassis_twist_init)
{
        _dynamics.acc_num = 1;
        _dynamics.acc_den = 7;
        _dynamics.brake_num = 1;
        _dynamics.brake_denom = 2;
}

#define mmToTicks(mm) ((motor_path_t) (((motor_path_t) (mm) * 480) / 22))

void *chassis_twist_handler(char method, void *data, uint8_t *size)
{
        *size = 1;

        switch (method) {
                case 'g':
                        *size = sizeof (_twist);
                        return (void *) &_twist;
                        break;
                case 's':
                        _twist = *((struct chassis_twist *) data);
                        if (_twist.path != 0) {
                                chassis_move(_twist.left, _twist.right, 
                                      _dynamics.acc_num, _dynamics.acc_den,
                                      _twist.path);
                        } else {
                                chassis_write(_twist.left, _twist.right);
                        }
                default:
                        break;
        }
        
        return &default_y;
}

void *chassis_dynamics_handler(char method, void *data, uint8_t *size)
{
        *size = 1;

        if (method == 's') {
                _dynamics = *((struct chassis_dynamics *) data);
                chassis_setup_ebrake(_dynamics.brake_num, _dynamics.brake_denom);
        } else if (method == 'g') {
                *size = sizeof (_dynamics);
                return (void *) &_dynamics;
        }

        return &default_y;
}

void *chassis_state_handler(char method, void *data, uint8_t *size)
{
        *size = 1;
        static uint8_t state;
        state = chassis_busy();
        return (void *) &state;
}

/**
 * @}
 */

void *servo_handler(char method, void *data, uint8_t *size)
{
        static uint8_t states[CONFIG_ROBOT_NUM_SERVO + 1];
        static uint8_t dummy = 255;

        struct srv {
                uint8_t addr;
                uint8_t pos;
        } *srv = (struct srv *) data;

        *size = 1;

        if (method == 'g') {
                if (srv->addr > CONFIG_ROBOT_NUM_SERVO) {
                        return (void *) &dummy;
                } else {
                        return (void *) &states[srv->addr - 1];
                }       
        } else if (method == 's') {
                if (srv->addr <= CONFIG_ROBOT_NUM_SERVO) {
                        states[srv->addr - 1] = srv->pos;
                        servo_write(srv->addr, srv->pos);
                }
        }

        return &default_y;
}

void *led_handler(char method, void *data, uint8_t *size)
{
        *size = 1;

        GPIO_INIT_OUT(GPB0);

        if (method == 's') {
                uint8_t *d = (uint8_t *) data;
                if (*d) {
                        GPIO_WRITE_LOW(GPB0);
                } else {
                        GPIO_WRITE_HIGH(GPB0);
                }
        }

        return &default_y;
}

void *bsensor_handler(char method, void *data, uint8_t *size)
{
        *size = 1;
        
        if (method == 'g') {
                uint8_t index = *((uint8_t *) data);
                static uint8_t ret = 0;

                if (index == 0) {
                        ret = !GPIO_READ(GPE6);
                } else if (index == 1) {
                        ret = !GPIO_READ(GPB6);
                } else if (index == 2) {
                        ret = GPIO_READ(GPC6);
                } else if (index == 3) {
                        ret = GPIO_READ(GPB7);
                }

                ret = ret > 0;

                return &ret;
        }

        return &default_y;
}

void *odetect_handler(char method, void *data, uint8_t *size)
{
        *size = 1;

        if (method == 's') {
                uint8_t mask = *((uint8_t *) data);
                uint8_t values = *(((uint8_t *) data) + 1);

                odetect_set_limit(mask, values);
        }

        return &default_y;
}
