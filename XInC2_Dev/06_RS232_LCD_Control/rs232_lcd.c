/* Author: Thia Wyrod
 * License: GPLv3
 */
#include <IOConfig.h>
#include <Structs.h>

#include "RS232.h"
#include "LCD_commands.h"
#include "LCD_functions.h"
#include "time_funcs.h"
#include "buffered_button.h"
#include "struct_aliases.h"

#define BAUD_RATE 9600 //the default LCD baud rate, bits / s
#define TICK_RATE 49152000 // sysclock is 49.152 MHz
#define TICKS_PER_BIT TICK_RATE/BAUD_RATE+1 //ticks per bit to wait
/* We have different ports for each board because active-high buttons CANNOT
 * share a port with active-low IO pins. There are also significant layout
 * differences between boards.
 */
#ifdef __BOARD_GINGER__
#define data_pins { { GPIO_C, io_PC0, 0x1, Polar_ActiveLow },\
                    { GPIO_C, io_PC1, 0x2, Polar_ActiveLow }, TICKS_PER_BIT }
#define RTS_pin { GPIO_C, io_PC4, 0x10, Polar_ActiveLow }
#define CTS_pin { GPIO_C, io_PC5, 0x20, Polar_ActiveLow }

#elif defined(__BOARD_XINC2_DEV__)
#define data_pins { { GPIO_E, io_PE, 0x1, Polar_ActiveLow },\
                    { GPIO_E, io_PE, 0x2, Polar_ActiveLow }, TICKS_PER_BIT }
#define RTS_pin { GPIO_E, io_PE, 0x4, Polar_ActiveLow }
#define CTS_pin { GPIO_E, io_PE, 0x8, Polar_ActiveLow }

#endif //__BOARD_GINGER__

static const RS232_Pins lcd_pins = { data_pins, RTS_pin, CTS_pin };

static const uint16_t kMsPerButtonPoll = 10; //main loop polls buttons every 10 ms
static const uint16_t kMsPerButtonClick = 50;
static BufferedButton clear_switch = { SW3,
  kMsPerButtonClick/kMsPerButtonPoll, 0 };
static BufferedButton display_switch = { SW2,
  kMsPerButtonClick/kMsPerButtonPoll, 0 };
static BufferedButton shift_switch = { SW1,
  kMsPerButtonClick/kMsPerButtonPoll, 0 };

static GlobalPin const * const button_pins[] = { &clear_switch.gl_pin,
  &display_switch.gl_pin, &shift_switch.gl_pin };
static const size_t kNumButtonPins = sizeof(button_pins) / sizeof(*button_pins);

static GlobalPin const * const input_pins[] = { &lcd_pins.D.rx, &lcd_pins.CTS };
static const size_t kNumInputPins = sizeof(input_pins) / sizeof(*input_pins);

static GlobalPin const * const output_pins[] = { &lcd_pins.D.tx, &lcd_pins.RTS };
static const size_t kNumOutputPins = sizeof(output_pins) / sizeof(*output_pins);


int main(void)
{
  init_clock();
  for (size_t i = 0; i < kNumInputPins; ++i) {
    io_set_config(DEFAULT_IO_CFG, input_pins[i]->io_port);
    globalPin_set_dir(PinDir_Input, input_pins[i]);
  }
  for (size_t i = 0; i < kNumOutputPins; ++i) {
    io_set_config(DEFAULT_IO_CFG, output_pins[i]->io_port);
    globalPin_set_dir(PinDir_Output, output_pins[i]);
  }
  for (size_t i = 0; i < kNumButtonPins; ++i) {
    io_set_config(DEFAULT_BUTTON_CFG, button_pins[i]->io_port);
    globalPin_set_dir(PinDir_Input, button_pins[i]);
  }

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
