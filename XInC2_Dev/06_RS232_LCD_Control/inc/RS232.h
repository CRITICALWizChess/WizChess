/* Author: Thia Wyrod
 * License: GPLv3
 */
#ifndef _RS232_H_
#define _RS232_H_

#include <UART.h>

typedef struct RS232_Pins {
  UART_Pin_Pair const D;
  GlobalPin const RTS;
  GlobalPin const CTS;
} RS232_Pins;

static inline void rs232_write_byte(uint16_t byte, RS232_Pins const * pins)
{
  globalPin_write_raw(0, &pins->RTS); //send a request to send
  while(globalPin_read_raw(&pins->CTS)); //wait until cleared to send
  uart_write_byte(byte, &pins->D);
  globalPin_write_raw(1, &pins->RTS);
}

static inline uint16_t rs232_read_byte(RS232_Pins const * pins)
{
  while(globalPin_read_raw(&pins->CTS)); //wait until the device requests to send
  globalPin_write_raw(0, &pins->RTS); //notify the device that it is cleared to send
  uint16_t byte = uart_read_byte(&pins->D);
  globalPin_write_raw(1, &pins->RTS);
  return byte;
}

#endif //_RS232_H_
