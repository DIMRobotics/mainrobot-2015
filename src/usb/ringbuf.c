#include "usb/ringbuf.h"

void ringbuf_init(struct ringbuf *b)
{
        b->start = 0;
        b->end = 0;
}

uint8_t ringbuf_is_full(const struct ringbuf *b)
{
        return ((b->end + 1) % CONFIG_RINGBUF_SIZE) == b->start;
}

uint8_t ringbuf_is_empty(const struct ringbuf *b)
{
        return b->start == b->end;
}

void ringbuf_push(struct ringbuf *b, uint8_t byte)
{
        if (!ringbuf_is_full(b)) {
                b->data[b->end++] = byte;
                b->end %= CONFIG_RINGBUF_SIZE;
        }
}

uint8_t ringbuf_pull(struct ringbuf *b)
{
        if (!ringbuf_is_empty(b)) {
                uint8_t ret = b->data[b->start++];
                b->start %= CONFIG_RINGBUF_SIZE;
                return ret;
        }
        return 0;
}
