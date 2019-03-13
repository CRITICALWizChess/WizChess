#include <SystemClock.h>
#include <XPD.h>
#include <GPIO.h>
#include <Thread.h>

#include "main.h"

// sys_clock_wait can only wait a maximum of 65535 ticks
// use a loop to get a longer delay.
void long_wait()
{
  for (int i = 0; i < 5000; ++i) {
    sys_clock_wait(10000);
  }
}

// Thread that reads the state of a button and turns on an LED if the button
// is pressed.
// Threads must return (void *) and take an argument of (void *)
void *button_reading_thread(void *)
{
  // Thread 1 loop
  while (true) {
    uint16_t port_d_state = gpio_read(GPIO_D);
    bool is_button_pressed = (port_d_state & (1<<6));
    if (is_button_pressed) {
      gpio_write(0x01, GPIO_A);
    } else {
      gpio_write(0x00, GPIO_A);
    }
  }
}

// main() runs in thread 0
int main(void)
{
  // Set pin PC0 as output
  // Pins are set as an output by setting a 1 in position N+8, where N is
  // the GPIO pin number.
  gpio_set_config((0x01 << 8), GPIO_C);

  // Set pin PA0 as output
  // Pins are set as an output by setting a 1 in position N+8, where N is
  // the GPIO pin number.
  gpio_set_config((0x01 << 8), GPIO_A);

  // Set port D as inputs
  gpio_set_config((0x00 << 8), GPIO_D);

  // Configure thread 1
  thread_setup(button_reading_thread, NULL, 1);

  // Start thread 1
  thread_run(1);

  // Loop, printing Hello, World as well as a number
  // the number increments once per loop.
  // Also, toggle on and off an LED on the board.
  uint16_t count = 0;
  while (true) {
    xpd_puts("hot damn\n");
    xpd_puts("Loop counter is: ");
    xpd_echo_int(count, XPD_Flag_UnsignedDecimal);
    xpd_putc('\n');
    long_wait();
    count += 1;

    // Toggle the LED based on the loop counter
    if (count % 2) {
      gpio_write(0x01, GPIO_C);
    } else {
      gpio_write(0x00, GPIO_C);
    }
  }

  return 0;
}
