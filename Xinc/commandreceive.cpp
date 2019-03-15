//put the code for UART recieve and  command conversion here
/*also write functions for motor movement
void north( int); // input number of squares
void northeast( int);
void east( int);
void southeast(int);
void south(int)
void southwest(int);
void west(int);
void northwest(int);
void zero( void);
*/

#include <SystemClock.h>
#include <XPD.h>
#include <GPIO.h>
#include <Thread.h>
#include <UART.h>
#include <string.h>
#include <UARTPin.h>


#include "main.h"

#define SYS_FREQ 98304000 //uhhh right, confirm this before testing(huh)
#define BUFFER_SIZE 10

void UART_RECEIVEstring ( char* );
void long_wait( void );

 //UART_Pin_Pair uart_pair1;

//uart_pair1.rx.port = GPIO_B;
//uart_pair1.rx.io_port = io_PB0;

// Setting up a UART RX/TX pair on PC1/PC2 at 115200 baud
//  using RX = UARTPin<GPIO_C, 1, SYS_FREQ / 115200>;
//  using TX = UARTPin<GPIO_C, 2, SYS_FREQ / 115200>;
//
//  Reading a byte:
//    byte = RX::readByte();
//  Writing a byte:
//    TX::writeByte(byte);

int main(void){

  char movein[BUFFER_SIZE];
  
  // Set port D as inputs
  gpio_set_config((0x00 << 8), GPIO_D);
  // Set pin PC0 as output
  // Pins are set as an output by setting a 1 in position N+8, where N is
  // the GPIO pin number.
  gpio_set_config((0x01 << 8), GPIO_C);  

    uint16_t count = 0;
    while (true){

        //using RX = UARTPin<GPIO_C, 1, SYS_FREQ / 19200>;
        //using TX = UARTPin<GPIO_C, 2, SYS_FREQ / 19200>;
        //TX::

        UART_RECEIVEstring(movein);
        xpd_puts("uart recieved below\n");
        //movein[0] = '1';
        xpd_puts(movein);
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
}

void UART_RECEIVEstring ( char *receive){
    using RX = UARTPin<GPIO_C, 1, SYS_FREQ / 9600>;
    using TX = UARTPin<GPIO_C, 2, SYS_FREQ / 9600>;
    int i=0;
    while (i<BUFFER_SIZE){
        receive[i] = RX::readByte();
        if (receive[i]=='\n'){
            receive[i]='\0';
            break;
        }
      i += 1;
      //xpd_echo_int(i, XPD_Flag_UnsignedDecimal);
    }
}
void long_wait()
{
  for (int i = 0; i < 5000; ++i) {
    sys_clock_wait(10000);
  }
}