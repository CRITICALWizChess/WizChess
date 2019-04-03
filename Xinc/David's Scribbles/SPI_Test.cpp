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
#include "struct_aliases.h"

// We are utilizing SP1, SEN1 must be set low for transmission
// In slave mode the phase = 1, and polarity = 1
// SCK and MOSI = Inputs
// MISO is an output while SEN1 is Low and
// an Input when SEN1 is high

void SPI_init(void){
    SPI_set_config((SPI_ENABLE|SPI_MASTER),SPI1)
    // gnd SEN1 pin or PD3 on board
}

int main(void){
    SPI_set_config();
    int16_t config = 0;
    config = SPI_get_config(SPI1);
    xpd_echo_int(config, XPD_Flag_SignedDecimal);
}


