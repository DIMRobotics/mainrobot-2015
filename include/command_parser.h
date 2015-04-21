#ifndef INCLUDE_COMMAND_PARSER_H
#define INCLUDE_COMMAND_PARSER_H

/**
 * Command parser interface for Cerebellum project
 */

#include <stdint.h>
#include <stdio.h>

#include "cmd_handlers.h"
#include "usb/usb.h"

/** Command handler pointer - void *cmd_hndlr(char method, void * input) */
typedef void* (*cmd_handler)(char, void *, uint8_t *);

/**
 * Functions definition
 */

void *cmd_parse(char method, uint8_t addr, void *in, uint8_t *out_size);
cmd_handler cmd_set_handler(uint8_t addr, cmd_handler hndlr);

#endif
