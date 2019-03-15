/* Author: Thia Wyrod
 * License: GPLv3
 */
#ifndef _LCD_CMD_H_
#define _LCD_CMD_H_

#include <SXC.h>

const uint16_t kLCDPrefix = 0xFE;
const uint16_t kLCDReadCmd = 0x73;
const uint16_t kLCDCustomCharCmd = 0x54;
const size_t kLCDCustomCharLen = 9;

enum LCD_0Param_Cmd {
  LCD_Disp_On = 0x41,
  LCD_Disp_Off = 0x42,
  LCD_Disp_Clear = 0x51,
  LCD_Disp_ShLeft = 0x55,
  LCD_Disp_ShRight = 0x56,
  LCD_Curs_Home = 0x46,
  LCD_Curs_On = 0x47,
  LCD_Curs_Off = 0x48,
  LCD_Curs_Left = 0x49,
  LCD_Curs_Right = 0x4A,
  LCD_Curs_BlinkOn = 0x4B,
  LCD_Curs_BlinkOff = 0x4C,
  LCD_Curs_Backspace = 0x4E,
  LCD_Get_FW_Ver = 0x70,
  LCD_Get_Baud_Rate = 0x71,
  LCD_Get_I2C_Addr = 0x72
};

enum LCD_1Param_Cmd {
  LCD_Curs_SetPos = 0x45,
  LCD_Disp_SetContrast = 0x52,
  LCD_Disp_SetBacklight = 0x53,
  LCD_Set_Baud_Rate = 0x61,
  LCD_Set_I2C_Addr = 0x62
};
#endif //_LCD_CMD_H_
