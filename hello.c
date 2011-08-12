#include <avr/io.h>

void __attribute__ ((noreturn)) main( void ) {
    
    /*  set port B and D as output  */
    DDRB=0xFF;
    DDRD=0xFF;

    /*  set port C as input and activate internal pullup for pin 0 and 5
     */
    DDRC=0x00;
    PORTC=0x21;

    /*  turn all off for init   */
    PORTB=0xFF; /*  invers  */
    PORTD=0x00;

}
