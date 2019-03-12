//put the code for UART recieve and  command conversion here

#include <UARTPin.h>

// Setting up a UART RX/TX pair on PC1/PC2 at 115200 baud
//  using RX = UARTPin<GPIO_C, 1, SYS_FREQ / 115200>;
//  using TX = UARTPin<GPIO_C, 2, SYS_FREQ / 115200>;
//
//  Reading a byte:
//    byte = RX::readByte();
//  Writing a byte:
//    TX::writeByte(byte);

using RX = UARTPin<GPIO_C, 1, SYS_FREQ / 19200>;
using TX = UARTPin<GPIO_C, 2, SYS_FREQ / 19200>;

while
