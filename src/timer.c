#include <arch/antares.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>

#include <lib/tmgr.h>
#include <lib/cerebellum/gpio.h>
#include <lib/cerebellum/chassis.h>
#include <lib/cerebellum/stepper.h>
#include <robot/odetect.h>


ANTARES_INIT_HIGH(maintimer_init)
{
        GPIO_INIT_OUT(GPB0);
        //TCCR0A = (1<<WGM01);
        //TCCR0B = (1<<CS01)|(1<<CS00);
        TCCR0B = (1<<CS02) | (1<<CS00);
        //OCR0A = 250;
        OCR0A = 156;
        TIMSK0 |= (1<<OCIE0A);
}

ANTARES_APP(tmgr_app)
{
        tmgr_process();
}

static volatile int32_t timer = -1;

void timer_run(void)
{
        timer = 87000;
}

/**
 * Main robot task sheduler loop
 */

ISR(TIMER0_COMPA_vect)
{
        sei();

        tmgr_interrupt();
        #ifdef CONFIG_USE_ODETECT
        odetect_interrupt();
        #endif
        chassis_interrupt();
        if (timer > 0) {
                timer--;
                
                if (timer == 0) {
                        //GPIO_WRITE_HIGH(CONFIG_ROBOT_VACUUM);
                        //GPIO_WRITE_HIGH(GPB0);
                        //stepper_set_speed(0, 0);
                        //stepper_set_speed(1, 0);
                        //stepper_set_speed(2, 0);
                        //TCCR0B = 0;
                        exit(0);
                }
        }
        TCNT0 = 0;
}
