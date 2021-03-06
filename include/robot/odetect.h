#ifndef INCLUDE_ROBOT_ODETECT_H
#define INCLUDE_ROBOT_ODETECT_H

#include <stdint.h>

typedef enum {
        ODETECT_REAR = (1<<0),
        ODETECT_RIGHT = (1<<1),
        ODETECT_FRONT = (1<<5),
        ODETECT_LEFT = (1<<4),
        ODETECT_FLEFT = (1<<3),
        ODETECT_FRIGHT = (1<<2)
} odetect_dir_t;

void odetect_set_limit(odetect_dir_t dir, uint8_t limit);
void odetect_set_single_limit(odetect_dir_t dir, uint8_t limit);
uint8_t odetect_get_state(odetect_dir_t dir);
void odetect_write_state(odetect_dir_t dir, uint8_t state);
void odetect_interrupt(void);

#endif
