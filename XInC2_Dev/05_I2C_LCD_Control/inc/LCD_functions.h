/* Author: Thia Wyrod
 * License: GPLv3
 */
#ifndef _LCD_FUNC_H_
#define _LCD_FUNC_H_

#include <I2C.h>
#include "LCD_commands.h"

static const uint16_t kSlaveAddr = 0xA0;

/* Sends a 0-parameter command to the LCD */
static inline void LCD_send_0param_cmd(enum LCD_0Param_Cmd cmd,
  I2C_Pin_Pair const * pins)
{
  i2c_write_to_addr(kSlaveAddr, kLCDPrefix, pins);
  i2c_write_to_addr(kSlaveAddr, cmd, pins);
}

/* Sends a 1-parameter command to the LCD; only the LSB matters */
static inline void LCD_send_1param_cmd(enum LCD_1Param_Cmd cmd, uint16_t param,
  I2C_Pin_Pair const * pins)
{
  i2c_write_to_addr(kSlaveAddr, kLCDPrefix, pins);
  i2c_write_to_addr(kSlaveAddr, cmd, pins);
  i2c_write_to_addr(kSlaveAddr, param, pins);
}

/* Sends the custom character data at the 9-word array pointed to by bitmaps
 * (only the LSBs of the words matter). See the datasheet for detailed info.
 */
static inline void LCD_send_custom_char(uint16_t* bitmaps,
  I2C_Pin_Pair const * pins)
{
  i2c_write_to_addr(kSlaveAddr, kLCDPrefix, pins);
  i2c_write_to_addr(kSlaveAddr, kLCDCustomCharCmd, pins);
  for (size_t i = 0; i < kLCDCustomCharLen; ++i)
    i2c_write_to_addr(kSlaveAddr, bitmaps[i], pins);
}

/* Reads the char at the current cursor location. Unknown return value if
 * non-ASCII. MSB of return value is garbage. */
static inline uint16_t LCD_read(I2C_Pin_Pair const * pins)
{
  i2c_write_to_addr(kSlaveAddr, kLCDPrefix, pins);
  i2c_write_to_addr(kSlaveAddr, kLCDReadCmd, pins);
  i2c_write_to_addr(kSlaveAddr, 0, pins);
  return i2c_read_byte(0, pins);
}

#endif //_LCD_FUNC_H_
