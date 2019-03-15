/* Author: Thia Wyrod
 * License: GPLv3
 */
#include <IOConfig.h>
#include <Structs.h>
#include <ADC.h>
#include <XPD.h>

#include "time_funcs.h"
#include "buffered_button.h"
#include "struct_aliases.h"

static const size_t kMsPerPoll = 500;

static uint16_t volt_to_temper(uint16_t val)
{
  //insert the appropriate scaling factor and other operations as needed to
  //convert the ADC voltage 10-bit value to a temperature
  return val & 0x3FF;
}

//As per the documentation, the maximum ADC clock frequency is 625 kHz. Because
//the system clock is ~49 MHz, we MUST divide the clock by AT LEAST ~78
static const uint16_t kADCcfg = ADC_CLK_RATE_DIV_128|ADC_CONT_SAMPLING|
  ADC_ENABLE_FLOW_CONTROL|ADC_THREE_CHANNEL_MODE;
static const uint16_t kChannelNums[] = {1, 1, 1};

int main(void)
{
  init_clock();
  ADC_set_config(kADCcfg);
  ADC_set_channel_nums(kChannelNums);
  ADC_set_clock_wait(0); //sample continuously at the ADC clock rate
  ADC_power_on();
  ADC_start(); //continuous sampling mode, we only need to start once
  while (1) {
    xpd_echo_int(volt_to_temper(ADC_read()), XPD_Flag_Hex);
    xpd_putc('\n');
    wait_ms(kMsPerPoll);
  }
  ADC_power_off();
  return 0;
}
