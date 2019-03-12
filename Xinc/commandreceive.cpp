//put the code for UART recieve and  command conversion here

#include <UARTPin.h>
#include <SystemClock.h>
#include <XPD.h>
#include <GPIO.h>
#include <Thread.h>

#define SYS_FREQ 100000000 //uhhh right, confirm this before testing
#define BUFFER_SIZE 10

void UART_RECEIVEstring ( char* );
void long_wait( void );

char movein[BUFFER_SIZE];

// Setting up a UART RX/TX pair on PC1/PC2 at 115200 baud
//  using RX = UARTPin<GPIO_C, 1, SYS_FREQ / 115200>;
//  using TX = UARTPin<GPIO_C, 2, SYS_FREQ / 115200>;
//
//  Reading a byte:
//    byte = RX::readByte();
//  Writing a byte:
//    TX::writeByte(byte);

int main(void){

    using RX = UARTPin<GPIO_C, 1, SYS_FREQ / 19200>;
    using TX = UARTPin<GPIO_C, 2, SYS_FREQ / 19200>;

    uint16_t count = 0;
    while (true){

        UART_RECEIVEstring(movein);
        xpd_puts("Hello, world!\n");
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
}

void UART_RECEIVEstring ( char *recieve ){
    int i=0;
    while (i<BUFFER_SIZE){
        receive[i] = RX::readByte();
        if (recieve[i]=='\n'){
            recieve[i]='\0';
            break
        }
    }
}
void long_wait()
{
  for (int i = 0; i < 5000; ++i) {
    sys_clock_wait(10000);
  }
}