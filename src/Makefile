# Main objects for robot
objects-y += main.o timer.o init.o
objects-$(CONFIG_USE_ODETECT) += odetect.o uart.o
objects-$(CONFIG_USE_SERVO)+=servo.o #cannon.o elevator.o

# Command parser
objects-$(CONFIG_USE_REMOTE) += command_parser.o cmd_handlers.o

# Extra robot controlling functions
objects-$(CONFIG_USE_EXTRA) += extra.o

# USB support
subdirs-$(CONFIG_USE_USB) += usb

cflags-y+=-DCONFIG_ROBOT_LIMITER_LEFT=$(call unquote,$(CONFIG_ROBOT_LIMITER_LEFT_Q))
cflags-y+=-DCONFIG_ROBOT_LIMITER_RIGHT=$(call unquote,$(CONFIG_ROBOT_LIMITER_RIGHT_Q))
cflags-y+=-DCONFIG_ROBOT_SHMORGALKA=$(call unquote,$(CONFIG_ROBOT_SHMORGALKA_Q))
cflags-y+=-DCONFIG_ROBOT_VACUUM=$(call unquote,$(CONFIG_ROBOT_VACUUM_Q))
cflags-y+=-DCONFIG_ROBOT_ELEVRESET=$(call unquote,$(CONFIG_ROBOT_ELEVRESET_Q))
cflags-y+=-DCONFIG_ROBOT_SELECTOR=$(call unquote,$(CONFIG_ROBOT_SELECTOR_Q))

cflags-y+=-DCONFIG_ROBOT_SERVO1=$(call unquote,$(CONFIG_ROBOT_SERVO1_Q))
cflags-y+=-DCONFIG_ROBOT_SERVO2=$(call unquote,$(CONFIG_ROBOT_SERVO2_Q))
cflags-y+=-DCONFIG_ROBOT_SERVO3=$(call unquote,$(CONFIG_ROBOT_SERVO3_Q))
cflags-y+=-DCONFIG_ROBOT_SERVO4=$(call unquote,$(CONFIG_ROBOT_SERVO4_Q))
