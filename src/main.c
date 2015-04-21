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

/*
 * PF0 - relay
 * PB6 - limiter left
 * PE6 - limiter right
 * PC6 - shmorgalka
 */

/**
 * Enable stepper motor driver
 */
ANTARES_INIT_HIGH(init_stepper)
{
        stepper_enable();
}

/**
 * Set command parsers
 */

//void str_send(void *data);

//TMGR_DEFINE_TIMER(stringsender, str_send, NULL, 0);

#if 0
void str_send(void *d)
{
        /*if (cdc_status()) {
                static int counter = 0;

                fprintf(cdc_getfile(), "Hello World! %d\r\n", counter++);
                static uint8_t state = 0;

                if (state)
                        GPIO_WRITE_HIGH(GPB0);
                else
                        GPIO_WRITE_LOW(GPB0);

                state = !state;
        }
        
        static uint8_t servo_pos = 65;
        static uint8_t servo_dir = 1;
        servo_write(1, servo_pos);
        
        if (servo_dir) {
                servo_pos += 5;
                if (servo_pos == 160)
                        servo_dir = 0;
        } else {
                servo_pos -= 5;
                if (servo_pos == 70)
                        servo_dir = 1;
        }*/
        
        stringsender.expires += tmgr_ms_to_ticks(300);
        tmgr_add_timer(&stringsender);
}

ANTARES_INIT_HIGH(init_stringsender)
{
        GPIO_INIT_OUT(GPB0);
        tmgr_add_timer(&stringsender);        
}
#endif

/*
ANTARES_APP(led_blink)
{
        cdc_send("Hello World!\r\n", sizeof("Hello World!\r\n"));      
        GPIO_WRITE_LOW(GPB0);
        tmgr_delay_ms(100);
        GPIO_WRITE_HIGH(GPB0);
        tmgr_delay_ms(100);

}*/

ANTARES_INIT_HIGH(servo_pos)
{
        servo_write(1, 87);
        servo_write(2, 80);
        servo_write(3, 40);
        servo_write(4, 60);
}
/*
ANTARES_APP(cdc_input)
{
        int byte = cdc_recv_byte();
        cdc_send_byte(byte);
}
*/
/*
ANTARES_APP(action)
{
        chassis_move(10, 10, 1, 7, mmToTicks(100));
        while (chassis_busy());;;

        servo_write(2, 90);
        tmgr_delay(50);

        chassis_move(10, 10, 1, 7, mmToTicks(200));
        servo_write(1, 48);
        while(chassis_busy());;;

        servo_write(2, 60);
        tmgr_delay(50);

        chassis_move(-10, -10, 1, 7, mmToTicks(20));
        while (chassis_busy());;;
        servo_write(1, 27);
        tmgr_delay(150);
        chassis_move(10, 10, 1, 7, mmToTicks(20));
        while (chassis_busy());;;
        servo_write(2, 90);
        tmgr_delay(50);
        servo_write(1, 48);
        tmgr_delay(150);

        while (1);;;
}
ANTARES_APP(cmd_handler_task)
{
        //servo_write(3, 120);
        char mode = cdc_recv_byte();
        cdc_send_byte(mode);
        if (mode != 'g' && mode != 's')
                return;
        GPIO_WRITE_LOW(GPB0);

        //servo_write(3, 160);

        uint8_t addr = cdc_recv_byte();
        uint8_t size = cdc_recv_byte();

        static uint8_t buffer[257];
        cdc_recv(buffer, size);

        void *result = cmd_parse(mode, addr, buffer);

        result = result;
        GPIO_WRITE_HIGH(GPB0);
}*/
