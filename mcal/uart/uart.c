#include "uart.h"

uint8_t init_uart(void)
{
  /// baud rate
  /// data size
  /// stop bit
  /// parity
  /// transmitter enable
  UCSRC |= (1 << URSEL) | (1 << UCSZ1) | (1 << UCSZ0); /// 8 bit date size,
                                                       /// stop bit 1 bit
                                                       /// no parity
                                                       /// asynchronous mode
  UCSRB |= (1 << TXEN);                                /// transmitter enable
  UBRRL = 6;

  return 0;
}

static uint8_t uart_transmit(char data)
{

  while (!(UCSRA & (1 << UDRE)))
    ;
  UDR = data;

  return 0;
}

uint8_t uart_put(char *data, uint8_t size)
{
  if (!data)
    return 1;

  if (data[size] != '\0')
    return 1;

  while (data++)
  {
    uart_transmit(*data);
  }
  return 0;
}
