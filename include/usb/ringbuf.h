#ifndef _INCLUDE_USB_RINGBUF_H_
#define _INCLUDE_USB_RINGBUF_H_

#include <stdint.h>

struct ringbuf {
        uint8_t start;
        uint8_t end;
        uint8_t data[CONFIG_RINGBUF_SIZE];
};

void ringbuf_init(struct ringbuf *b);
uint8_t ringbuf_is_full(const struct ringbuf *b);
uint8_t ringbuf_is_empty(const struct ringbuf *b);
void ringbuf_push(struct ringbuf *b, uint8_t byte);
uint8_t ringbuf_pull(struct ringbuf *b);

#endif
