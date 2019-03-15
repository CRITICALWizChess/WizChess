/* Author: Thia Wyrod
 * License: GPLv3
 */
#ifndef _LCD_FUNC_H_
#define _LCD_FUNC_H_

#include "LCD_commands.h"
#include "RS232.h"

/* Sends a 0-parameter command to the LCD */
static inline void LCD_send_0param_cmd(enum LCD_0Param_Cmd cmd,
  RS232_Pins const * pins)
{
  rs232_write_byte(kLCDPrefix, pins);
  rs232_write_byte(cmd, pins);
}

/* Sends a 1-parameter command to the LCD; only the LSB matters */
static inline void LCD_send_1param_cmd(enum LCD_1Param_Cmd cmd, uint16_t param,
  RS232_Pins const * pins)
{
  rs232_write_byte(kLCDPrefix, pins);
  rs232_write_byte(cmd, pins);
  rs232_write_byte(param, pins);
}

/* Sends the custom character data at the 9-word array pointed to by bitmaps
 * (only the LSBs of the words matter). See the datasheet for detailed info.
 */
static inline void LCD_send_custom_char(uint16_t* bitmaps,
  RS232_Pins const * pins)
{
  rs232_write_byte(kLCDPrefix, pins);
  rs232_write_byte(kLCDCustomCharCmd, pins);
  for (size_t i = 0; i < kLCDCustomCharLen; ++i)
    rs232_write_byte(bitmaps[i], pins);
}

/* Reads the char at the current cursor location. Unknown return value if
 * non-ASCII */
static inline uint16_t LCD_read(RS232_Pins const * pins)
{
  rs232_write_byte(kLCDPrefix, pins);
  rs232_write_byte(kLCDReadCmd, pins);
  rs232_write_byte(0, pins);
  return rs232_read_byte(pins);
}

#endif //_LCD_FUNC_H_
