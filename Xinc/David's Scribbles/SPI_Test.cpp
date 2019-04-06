// SPI TEST STUFF
// David Gingles
// attempting to set up our own spi initalization and communication
// using the xinc as the slave #BDSM

#include <IOConfig.h>
#include <Structs.h>
#include <SPI.h>
#include <SystemClock.h>
#include <XPD.h>
#include <GPIO.h>

#include "time_funcs.h"
#include "buffered_button.h"
#include "struct_aliases.h"

//for some reason this thing doesnt look in struct_aliases so i put stuff here
#define DEFAULT_POLARITY Polar_ActiveLow
#define BUTTON_POLARITY Polar_ActiveHigh
#define LED_POLARITY DEFAULT_POLARITY
#define DEFAULT_IO_CFG IO_FAST_SLEW|IO_PULL_UP|IO_PULL_ENABLE|IO_DRIVE_4mA
#define DEFAULT_LED_CFG DEFAULT_IO_CFG
#define DEFAULT_BUTTON_CFG IO_FAST_SLEW|IO_PULL_DOWN|IO_PULL_ENABLE|IO_DRIVE_4mA
#define LED4 { GPIO_D, io_PD7, 0x80, LED_POLARITY }
#define SW2 { GPIO_A, io_PA, 0x4, BUTTON_POLARITY }
#define SW3 { GPIO_A, io_PA, 0x8, BUTTON_POLARITY }


// We are utilizing SP1, SEN1 must be set low for transmission
// In slave mode the phase = 1, and polarity = 1
// SCK and MOSI = Inputs
// MISO is an output while SEN1 is Low and
// an Input when SEN1 is high

int16_t exit = 0;
int16_t data1 = 0;

static const GlobalPin compare_LED = LED4;
static const uint16_t kMsPerButtonPoll = 10; //main loop polls buttons every 10 ms
static const uint16_t kMsPerButtonClick = 50;
static BufferedButton write_switch = { SW3,
  kMsPerButtonClick/kMsPerButtonPoll, 0 };
static BufferedButton read_switch = { SW2,
  kMsPerButtonClick/kMsPerButtonPoll, 0 };

static GlobalPin const * const input_pins[] = { &write_switch.gl_pin,
  &read_switch.gl_pin
};
static const size_t kNumInputPins = sizeof(input_pins) / sizeof(*input_pins);


static void read_EEPROM(enum SPI_name spi)
{
  //while (condition) {
  //  uint16_t data = SPI_read(spi);
  //}
}

static void write_EEPROM(enum SPI_name spi)
{
  //while (condition) {
  //  SPI_write(data, spi);
  //}
}

int main(void)
{
  init_clock();
  int16_t something = 0;
  SPI_set_config((SPI_ENABLE|SPI_MASTER),SPI1);
  something = SPI_get_config(SPI1);
  for (size_t i = 0; i < kNumInputPins; ++i) {
    io_set_config(DEFAULT_BUTTON_CFG, input_pins[i]->io_port);
    globalPin_set_dir(PinDir_Input, input_pins[i]);
  }
  io_set_config(DEFAULT_LED_CFG, compare_LED.io_port);
  globalPin_set_dir(PinDir_Output, &compare_LED);
  xpd_echo_int(something, XPD_Flag_UnsignedDecimal);

  while(exit == 0) {
    data1 = SPI_read(SPI1);
    xpd_echo_int(data1, XPD_Flag_UnsignedDecimal);
    wait_ms(10);
  }
  return 0;
}



