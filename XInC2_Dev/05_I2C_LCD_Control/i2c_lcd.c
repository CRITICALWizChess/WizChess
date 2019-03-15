/* Author: Thia Wyrod
 * License: GPLv3
 */
#include <IOConfig.h>
#include <Structs.h>
#include <I2C.h>

#include "LCD_commands.h"
#include "LCD_functions.h"
#include "time_funcs.h"
#include "buffered_button.h"
#include "struct_aliases.h"

#define LCD_MAX_FREQ 100000 //Hz
#define SELECTED_FREQ LCD_MAX_FREQ/10
#define TICK_RATE 49152000 // sysclock is 49.152 MHz
#define TICKS_PER_CLK TICK_RATE/SELECTED_FREQ+1
static const uint16_t kBoardI2CAddr = 0xFF5E; //this is arbitrary
/* We have different ports for each board because active-high buttons CANNOT
 * share a port with active-low IO pins. There are also significant layout
 * differences between boards.
 */
#ifdef __BOARD_GINGER__
#define i2c_pin_vals { GPIO_C, io_PC0, 0x1, Polar_ActiveLow },\
                     { GPIO_C, io_PC1, 0x2, Polar_ActiveLow }
#elif defined(__BOARD_XINC2_DEV__)
#define i2c_pin_vals { GPIO_E, io_PE, 0x1, Polar_ActiveLow },\
                     { GPIO_E, io_PE, 0x2, Polar_ActiveLow }
#endif //__BOARD_GINGER__

static const I2C_Pin_Pair lcd_pins = { i2c_pin_vals, kBoardI2CAddr,
  TICKS_PER_CLK };

static const uint16_t kMsPerButtonPoll = 10; //main loop polls buttons every 10 ms
static const uint16_t kMsPerButtonClick = 50;
static BufferedButton clear_switch = { SW3,
  kMsPerButtonClick/kMsPerButtonPoll, 0 };
static BufferedButton display_switch = { SW2,
  kMsPerButtonClick/kMsPerButtonPoll, 0 };
static BufferedButton shift_switch = { SW1,
  kMsPerButtonClick/kMsPerButtonPoll, 0 };

static GlobalPin const * const global_pins[] = { &clear_switch.gl_pin,
  &display_switch.gl_pin, &shift_switch.gl_pin, &lcd_pins.sda, &lcd_pins.scl };
static const size_t kNumGlobalPins = sizeof(global_pins) / sizeof(*global_pins);

int main(void)
{
  init_clock();
  for (size_t i = 0; i < kNumGlobalPins; ++i) {
    io_set_config(DEFAULT_IO_CFG, global_pins[i]->io_port);
    globalPin_set_dir(PinDir_Input, global_pins[i]);
  }
  i2c_init(&lcd_pins);

  while(1) {
    if ( read_buf_button(&clear_switch) ) {
      LCD_send_0param_cmd(LCD_Disp_Clear, &lcd_pins);
    }
    else if ( read_buf_button(&display_switch) ) {
      LCD_send_0param_cmd(LCD_Disp_On, &lcd_pins);
    }
    else if ( read_buf_button(&shift_switch) ) {
      LCD_send_0param_cmd(LCD_Disp_ShLeft, &lcd_pins);
    }
    wait_ms(kMsPerButtonPoll);
  }
  return 0;
}
