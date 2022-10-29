/******************************************************************************
 * File:             uart.h
 *
 * Author:           Omar Elmasri
 * Created:          10/29/22
 *                   UART controller for ATmega32
 *****************************************************************************/

#include <avr/io.h>
#include <avr/iom32.h>
#include <stdlib.h>

uint8_t init_uart(void);
uint8_t uart_put(char *data, uint8_t size);

