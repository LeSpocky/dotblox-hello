#include <avr/io.h> /* makefile finds iom168.h and iomx8.h  */
#include <avr/interrupt.h>

#include <string.h>

#include <util/delay.h>

static unsigned char    framebuffer[8][8];  /* [row][col]   */

ISR(TIMER0_OVF_vect) {
    static unsigned char    curr_col = 0;
    unsigned char           i, data;

    data = 0x00;

    for ( i=0; i<8; i++ ) {
        if ( framebuffer[i][curr_col] > 0 ) {
            data |= 1<<i;
        }
    }

    PORTB = 0xFF;
    PORTD = data;
    PORTB &= ~(1<<curr_col++);
    curr_col &= 0x07;   /*  7 to 0  */
}

void __attribute__ ((noreturn)) main( void ) {
    unsigned char   i, j;
    
    /*  set port B and D as output  */
    DDRB=0xFF;
    DDRD=0xFF;

    /*  set port C as input and activate internal pullup for pin 0 and 5
     */
    DDRC=0x00;
    PORTC=0x21;

    /*  turn all off for init   */
    PORTB=0xFF; /*  pnp transistors, invers  */
    PORTD=0x00;

    /*  init timer 0 for multiplexing int   */
    TCCR0B = 0x02;  /*  clk / 8 */
    TIMSK0 = 1<<TOIE0;

    /*  clear framebuffer   */
    memset( framebuffer, 0, 8*8 );

    sei();  /* set interrupt, pseudo c function */

    while ( 1 ) {
        for ( i=0; i<8; i++ ) {
            for ( j=0; j<8; j++ ) {
                framebuffer[i][j] ^= 1;
                _delay_ms(250);
            }
        }
    }
}

