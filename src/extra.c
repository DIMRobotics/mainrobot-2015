#include <robot/extra.h>

void catch_stand_open()
{
        servo_write(2, 95);
        tmgr_delay(500);
}

void catch_stand_close()
{
        servo_write(2, 126);
        tmgr_delay(500);
}

void elevator_middle()
{
        servo_write(1, 0);
        tmgr_delay(700);
        servo_write(1, 30);
}

void elevator_up()
{
        servo_write(1, 80);
        tmgr_delay(900);
        servo_write(1, 42);
}

void elevator_up_steady()
{
        servo_write(1, 80);
        tmgr_delay(300);
        servo_write(1, 42);
}

void elevator_down()
{
        servo_write(1, 0);
        tmgr_delay(600);
        servo_write(1, 20);
}

void paw_open()
{
        servo_write(3, 120);
}

void paw_close()
{
        servo_write(3, 40);
}

void ball_holder_open()
{
        servo_write(4, 90);
}

void ball_holder_close()
{
        servo_write(4, 126);
}

uint8_t bsensor_get(uint8_t index)
{
        uint8_t ret = 0;

        if (index == 0) {
                ret = !GPIO_READ(GPE6);
        } else if (index == 1) {
                ret = !GPIO_READ(GPB6);
        } else if (index == 2) {
                ret = GPIO_READ(GPC6);
        } else if (index == 3) {
                ret = GPIO_READ(GPB7);
        }

        return ret > 0;
}

static struct chassis_dynamics dyns;

ANTARES_INIT_LOW(dynamics_init) 
{
        dyns.acc_num = 1;
        dyns.acc_den = 7;
        dyns.brake_num = 1;
        dyns.brake_denom = 2;
}

void twist(int16_t spd_left, int16_t spd_right, int32_t distance)
{
        if (distance != 0) {
                chassis_move(mmsToTicks(spd_left), mmsToTicks(spd_right), 
                                dyns.acc_num, 
                                dyns.acc_den, mmToTicks(distance));
        } else {
                chassis_write(spd_left, spd_right);
        }
}

void twist_block(int16_t spd_left, int16_t spd_right, int32_t distance)
{
        twist(spd_left, spd_right, distance);
        while (chassis_busy());
}

uint8_t twist_busy()
{
        return chassis_busy();
}

void twist_wait()
{
        while (chassis_busy());
}

void twist_rotate(int16_t speed, int16_t angle)
{
        twist(speed, -speed, angle * 22 * ROBOT_RADIUS / 7 / 180);
}

void twist_rotate_block(int16_t speed, int16_t angle)
{
        twist_rotate(speed, angle);
        while (chassis_busy());
}


void dynamics(int16_t acc_num, int16_t acc_den, int16_t brake_num, int16_t brake_den)
{
        dyns.acc_num = acc_num;
        dyns.acc_den = acc_den;
        dyns.brake_num = brake_num;
        dyns.brake_denom = brake_den;
}
