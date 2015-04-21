/*
             LUFA Library
     Copyright (C) Dean Camera, 2014.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2014  Dean Camera (dean [at] fourwalledcubicle [dot] com)

  Permission to use, copy, modify, distribute, and sell this
  software and its documentation for any purpose is hereby granted
  without fee, provided that the above copyright notice appear in
  all copies and that both that the copyright notice and this
  permission notice and warranty disclaimer appear in supporting
  documentation, and that the name of the author not be used in
  advertising or publicity pertaining to distribution of the
  software without specific, written prior permission.

  The author disclaims all warranties with regard to this
  software, including all implied warranties of merchantability
  and fitness.  In no event shall the author be liable for any
  special, indirect or consequential damages or any damages
  whatsoever resulting from loss of use, data or profits, whether
  in an action of contract, negligence or other tortious action,
  arising out of or in connection with the use or performance of
  this software.
*/

/** \file
 *
 *  Main source file for the VirtualSerial demo. This file contains the main tasks of
 *  the demo and is responsible for the initial application hardware configuration.
 */

#include "usb/usb.h"
#include <lib/cerebellum/gpio.h>

/** LUFA CDC Class driver interface configuration and state information. This structure is
 *  passed to all CDC Class driver functions, so that multiple instances of the same class
 *  within a device can be differentiated from one another.
 */
USB_ClassInfo_CDC_Device_t VirtualSerial_CDC_Interface =
{
	.Config =
	{
		.ControlInterfaceNumber   = INTERFACE_ID_CDC_CCI,
		.DataINEndpoint           =
                {
                        .Address          = CDC_TX_EPADDR,
                        .Size             = CDC_TXRX_EPSIZE,
                        .Banks            = 1,
                },
		.DataOUTEndpoint =
		{
			.Address          = CDC_RX_EPADDR,
			.Size             = CDC_TXRX_EPSIZE,
			.Banks            = 1,
		},
		.NotificationEndpoint =
		{
			.Address          = CDC_NOTIFICATION_EPADDR,
			.Size             = CDC_NOTIFICATION_EPSIZE,
			.Banks            = 1,
		},
	},
};

static uint8_t usb_state = 0;

static struct ringbuf rx_buf, tx_buf;

uint8_t cdc_status(void)
{
        return usb_state;
}

uint8_t cdc_recv_avail(void)
{
        return !ringbuf_is_empty(&rx_buf);
}

uint8_t cdc_recv_byte(void)
{
        return ringbuf_pull(&rx_buf);
}

void cdc_recv(void *buf, uint8_t size)
{
        char *b = (char *) buf;
        while (size--)
                *b++ = cdc_recv_byte();
}

void cdc_send_byte(uint8_t byte)
{
        ringbuf_push(&tx_buf, byte);
}

void cdc_send(const void *buf, uint8_t size)
{
        char *b = (char *) buf;
        while (size--)
                cdc_send_byte(*b++);
}

/** Standard file stream for the CDC interface when set up, so that the virtual CDC COM port can be
 *  used like any regular character stream in the C APIs.
 */
static FILE USBSerialStream;

FILE* cdc_getfile()
{
        return &USBSerialStream;
}

ANTARES_INIT_LOW(_usb_init)
{
        /* Init RX and TX ring buffers */
        ringbuf_init(&rx_buf);
        ringbuf_init(&tx_buf);

        /* Disable clock prescaler */
        MCUSR &= ~(1 << WDRF);
        wdt_disable();
	clock_prescale_set(clock_div_1);
        USB_Init();
	
        /* Create a regular character stream for the interface so that it 
         * can be used with the stdio.h functions */
        CDC_Device_CreateBlockingStream(&VirtualSerial_CDC_Interface, 
                                        &USBSerialStream);
}


ANTARES_APP(_usb_loop)
{
        /* Receive byte if available */
        int16_t r = 0;
        if (!ringbuf_is_full(&rx_buf) && 
            (r = CDC_Device_ReceiveByte(&VirtualSerial_CDC_Interface)) >= 0) {
                ringbuf_push(&rx_buf, r & 0xFF);
        }

        if (!ringbuf_is_empty(&tx_buf)) {
                CDC_Device_SendByte(&VirtualSerial_CDC_Interface, 
                                        ringbuf_pull(&tx_buf));
        }
        
        /* perform all pending actions with USB */
        CDC_Device_USBTask(&VirtualSerial_CDC_Interface);
        USB_USBTask();
}

/** Event handler for the library USB Configuration Changed event. */
void EVENT_USB_Device_ConfigurationChanged(void)
{
        CDC_Device_ConfigureEndpoints(&VirtualSerial_CDC_Interface);

}

void EVENT_USB_Device_ControlRequest(void)
{
        CDC_Device_ProcessControlRequest(&VirtualSerial_CDC_Interface);
}

void EVENT_USB_Device_Connect(void)
{
        usb_state = 1;
        //GPIO_WRITE_LOW(GPB0);
}

void EVENT_USB_Device_Disconnect(void)
{
        usb_state = 0;
        //GPIO_WRITE_HIGH(GPB0);
}
#if 0
int main(void)
{

	for (;;)
	{
		CheckJoystickMovement();

		/* Must throw away unused bytes from the host, or it will lock up while waiting for the device */
		CDC_Device_ReceiveByte(&VirtualSerial_CDC_Interface);

		CDC_Device_USBTask(&VirtualSerial_CDC_Interface);
		USB_USBTask();
	}
}

/** Checks for changes in the position of the board joystick, sending strings to the host upon each change. */
void CheckJoystickMovement(void)
{
	uint8_t     JoyStatus_LCL = Joystick_GetStatus();
	char*       ReportString  = NULL;
	static bool ActionSent    = false;

	if (JoyStatus_LCL & JOY_UP)
	  ReportString = "Joystick Up\r\n";
	else if (JoyStatus_LCL & JOY_DOWN)
	  ReportString = "Joystick Down\r\n";
	else if (JoyStatus_LCL & JOY_LEFT)
	  ReportString = "Joystick Left\r\n";
	else if (JoyStatus_LCL & JOY_RIGHT)
	  ReportString = "Joystick Right\r\n";
	else if (JoyStatus_LCL & JOY_PRESS)
	  ReportString = "Joystick Pressed\r\n";
	else
	  ActionSent = false;

	if ((ReportString != NULL) && (ActionSent == false))
	{
		ActionSent = true;

		/* Write the string to the virtual COM port via the created character stream */
		fputs(ReportString, &USBSerialStream);

		/* Alternatively, without the stream: */
		// CDC_Device_SendString(&VirtualSerial_CDC_Interface, ReportString);
	}
}

/** Event handler for the library USB Connection event. */
void EVENT_USB_Device_Connect(void)
{
	LEDs_SetAllLEDs(LEDMASK_USB_ENUMERATING);
}

/** Event handler for the library USB Disconnection event. */
void EVENT_USB_Device_Disconnect(void)
{
	LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);
}

/** Event handler for the library USB Configuration Changed event. */
void EVENT_USB_Device_ConfigurationChanged(void)
{
	bool ConfigSuccess = true;

	ConfigSuccess &= CDC_Device_ConfigureEndpoints(&VirtualSerial_CDC_Interface);

	LEDs_SetAllLEDs(ConfigSuccess ? LEDMASK_USB_READY : LEDMASK_USB_ERROR);
}

/** Event handler for the library USB Control Request reception event. */
void EVENT_USB_Device_ControlRequest(void)
{
	CDC_Device_ProcessControlRequest(&VirtualSerial_CDC_Interface);
}

#endif
