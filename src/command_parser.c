#include "command_parser.h"

/**
 * Command structure:
 * 1. Get/set - 1 byte ('g'/'s')
 * 2. Address - 1 byte (0 - CONFIG_REMOTE_ADDR_MAX)
 * 3. Data length - 1 byte (0 - 255) (for Set requests only)
 * 3. Data - 'length' bytes
 */

static volatile cmd_handler handlers[CONFIG_REMOTE_ADDR_MAX];

void *cmd_parse(char action, uint8_t addr, void *in, uint8_t *out_size)
{
        if (addr >= CONFIG_REMOTE_ADDR_MAX) {
                *out_size = 0;
                return NULL;
        }

        if (handlers[addr] != NULL) {
                return handlers[addr](action, in, out_size);
        } else {
                *out_size = 0;
                return NULL;
        }
}

cmd_handler cmd_set_handler(uint8_t addr, cmd_handler hndlr)
{
        if (addr >= CONFIG_REMOTE_ADDR_MAX)
                return NULL;

        cmd_handler old = handlers[addr];
        handlers[addr] = hndlr;
        return old;
}

ANTARES_INIT_HIGH(cmd_hndlr_init)
{
        cmd_set_handler(1, chassis_twist_handler);
        cmd_set_handler(2, chassis_dynamics_handler);
        cmd_set_handler(3, servo_handler);
        cmd_set_handler(5, led_handler);
        cmd_set_handler(6, chassis_state_handler);
        cmd_set_handler(7, bsensor_handler);
}


ANTARES_APP(cmd_hndlr)
{
        static enum {
                STATE_MODE = 0,
                STATE_ADDR,
                STATE_SIZE,
                STATE_DATA,
                STATE_REPLY
        } state = STATE_MODE;

        static uint8_t method = 0;
        static uint8_t address = 0;
        static uint8_t data_size = 0;
        static uint8_t i = 0;
        static uint8_t buffer[128];
        static uint8_t* reply = NULL;

        if (cdc_recv_avail()) {
                uint8_t byte = cdc_recv_byte();
         
                if (state == STATE_MODE) {
                        if (byte != 's' && byte != 'g') {
                                cdc_send_byte('n');
                                return;
                        } else {
                                state = STATE_ADDR;
                                method = byte;
                        }
                } else if (state == STATE_ADDR) {
                        address = byte;
                        state = STATE_SIZE;
                } else if (state == STATE_SIZE) {
                        data_size = byte;
                        if (byte != 0) {
                                state = STATE_DATA;
                                i = 0;
                        } else {
                                reply = (uint8_t *) cmd_parse(method, address,
                                                (void *) buffer, &data_size);
                                state = STATE_REPLY;
                        }
                } else if (state == STATE_DATA) {
                        buffer[i++] = byte;
                        if (i == data_size) {
                                reply = (uint8_t *) cmd_parse(method, address,
                                                (void *) buffer, &data_size);
                                state = STATE_REPLY;
                        }
                } 
                
                if (state == STATE_REPLY) {

                        /*if (method == 'g') {
                                cdc_send_byte('s');
                                if (reply != NULL) {
                                        cdc_send_byte(data_size);
                                        for (i=0; i<data_size; i++) {
                                                cdc_send_byte(reply[i]);
                                        }
                                }

                        } else {
                                if (reply != NULL) {
                                        cdc_send_byte(reply[0]);
                                } else {
                                        cdc_send_byte('y');
                                }
                        }
                        */
                        if (method == 's') {
                                if (reply != NULL) {
                                        cdc_send_byte(reply[0]);
                                } else {
                                        cdc_send_byte('y');
                                }
                        } else {
                                if (reply != NULL) {
                                        cdc_send_byte(data_size);
                                        for (i = 0; i < data_size; i++) {
                                                cdc_send_byte(reply[i]);
                                        }

                                } else {
                                        cdc_send_byte('y');
                                }

                        }

                        state = STATE_MODE;
                }
        }
}
