#include <SystemClock.h>
#include <XPD.h>
#include <GPIO.h>
#include <Thread.h>

#include "main.h"

// sys_clock_wait can only wait a maximum of 65535 ticks
// use a loop to get a longer delay.
void long_wait()
{
  for (int i = 0; i < 20; ++i) {
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
    bool is_button_pressed = (port_d_state & (1<<7));
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
  gpio_set_config((0xC0 << 8), GPIO_C);

  // Set pin PA0 as output
  // Pins are set as an output by setting a 1 in position N+8, where N is
  // the GPIO pin number.
  gpio_set_config((0xC0 << 8), GPIO_A);
  //gpio_set_config((0x01 << 9), GPIO_A);
  // Set port D as inputs
  gpio_set_config((0x01 << 8), GPIO_D);

  // Configure thread 1
  //thread_setup(button_reading_thread, NULL, 1);

  // Start thread 1
  //thread_run(1);

  // Loop, printing Hello, World as well as a number
  // the number increments once per loop.
  // Also, toggle on and off an LED on the board.
  uint16_t count = 0;
  uint16_t square = 0;
  while (true) {
    xpd_puts("Hello, world!\n");
    xpd_puts("Loop counter is: ");
    xpd_echo_int(count, XPD_Flag_UnsignedDecimal);
    xpd_putc('\n');
    long_wait();
    count += 1;
    square += 1;
    gpio_write(0x01, GPIO_D); //shuts of magnet 0x00 turns it on
    //gpio_write(0x80, GPIO_C); //East or Northeast
    //gpio_write(0x00, GPIO_C); //Northwest and north and west
    //gpio_write(0x40, GPIO_C); //South or Southwest 
    //gpio_write(0xC0, GPIO_C); //Southeast
  // Blue motor controls North and South
  // Red motor controls East and West 

    // Toggle the LED based on the loop counter
      for (int f = 0; f <= 1200; f++) // one square horizontal 1200 same for diagonal
      {
        gpio_write(0xC0, GPIO_A); //both motors
        //gpio_write(0x80, GPIO_A); //red motor motion
        //gpio_write(0x40, GPIO_A); //blue motor motion 
        long_wait();
        gpio_write(0x00, GPIO_A);
        long_wait();
      }
          if (square % 2) //direction switching
          { 
            gpio_write(0x40, GPIO_C); 
            //gpio_write(0x40, GPIO_C); //south and south west
            //gpio_write(0xC0, GPIO_C); //southeast
          }
          else 
          { 
            gpio_write(0x40, GPIO_C); 
            //gpio_write(0x80, GPIO_C); //east and northeast
            //gpio_write(0x00, GPIO_C); //south or southeast
          }
     //if (count % 2) {
      //gpio_write(0x00, GPIO_C)
      //gpio_write(0x80, GPIO_A);
    //} else {
      //gpio_write(0x00, GPIO_C);
      //gpio_write(0x00, GPIO_A);
    //}
  }
  return 0;
}
