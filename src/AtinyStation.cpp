/*
 AUTHOR: Zep Holleman
 Upload command: avrdude -c usbasp -B 5 -pt85 -U flash:w:firmware.hex
 firmware hex is in the directory .pio/build/ATiny85
*/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <Arduino.h>

#define RX 3 //PIN 2 on atiny
#define TX 4 //PIn 3 on atiny

#define ONE_METER 1
#define HALF_METER 2
#define QUARTER_METER 4
#define TOO_CLOSE
/*
    Systemclock : 1 000 000 hz
    prescalar   : 64
    
    FastPWM frequency = systemclock/(prescalar * 256)
    FastPWM frequency = 8000000/(64*256) = 488hz
    Source: ATiny85 datasheet
*/

int main(void)
{
    TCNT0 = 0;
    TCNT1 = 0;
    TCCR1 = 0;
    TCCR0A = 0;
    TCCR0B = 0;

    DDRB = (1 << PB0) | (1 << PB2);
    //Use pin pb0/pin5/0c0a
    TCCR0A |= (1 << WGM00) | (1 << WGM01);   //FAST-PWM mode
    TCCR0A |= (1 << COM0A0) | (1 << COM0A1); //SET on compare match, clear at bottom (TCNT0 == 0xff)
    TCCR0B |= (1 << CS00);                   //64 prescalar
    OCR0A = 120;                             //Defines

    OCR1A = 243;                                      // 1.0005763319672132 Hz (1000000/((243+1)*4096))
    TCCR1 |= (1 << CTC1);                             // Enables CTC mode
    TCCR1 |= (1 << CS13) | (1 << CS12) | (1 << CS10); //PRESCALER 4096
    TIMSK |= (1 << OCIE1A);                           //Enable output compare match interrupt
    sei();

    for (;;);
};

ISR(TIMER1_COMPA_vect)
{
    PORTB ^= (1 << PB2);
    TCCR0B ^= (1 << CS00);
}