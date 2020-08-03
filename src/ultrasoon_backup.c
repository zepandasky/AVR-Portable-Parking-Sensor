// /*
//  * input.c
//  *
//  *  Created on: May 23, 2020
//  *      Author: zep
//  *  Description:
//  *  Program to read values from ultra soon and send them through serial interface
//  */
// #ifndef BAUD
// #define BAUD 9600
// #endif

// #define DEBOUNCE_TIME 1000
// #define START_TIMER TCCR0B |= (1 << CS11)
// #define STOP_TIMER TCCR0B &= 0B11111000

// #include <avr/io.h>
// #include <avr/interrupt.h>
// #include <util/delay.h>
// #include <util/setbaud.h>
// #include <stdio.h>
// #include <stdlib.h>

// volatile int overflow_counter = 0;

// void initUsart()
// {
//     UCSR0B |= (1 << TXEN0) | (1<<RXEN0);
//     UCSR0C |= (1<<UCSZ00) | (1<<UCSZ01); //8 bit character size
//     UBRR0H = UBRRH_VALUE;
//     UBRR0L = UBRRL_VALUE;
// }

// void initTimer1()
// {
//     TCCR1A |= (1 << COM1A1);   //clear on compare match OC1A
//     TCCR1B |= (1 << WGM12); //ctc mode
// }

// void  initTimer0()
// {
//     TCCR0A |= (1 << WGM01);
// }

// void transmitByte(uint8_t data){
//   loop_until_bit_is_set(UCSR0A, UDRE0);
//   UDR0 = data;
// }

// int readValue()
// {
//     OCR1A = 20;
//     PORTB |= (1 << PB1);
//     START_TIMER;    
//     transmitByte('b');
//     while(PINB & (1 << PB1));
//     //Zet pin aan en blijf loopen todat deze pin weer uitgeschakeld is, dit gebeurt als het goed is na
//     // 10 uS
//     transmitByte('c');
//     if(overflow_counter == 14)
//         OCR0A = 166;
    
//     while(PINB & (1 << PB2));

//     //If pd2 is high even after delay time, then its not a bounce but a user button press
// //     if(!(PIND & (1 << PD2))){
//     int interval = TCNT0 + (overflow_counter * 255);
//     transmitByte('a');
//     return interval/58;
// }




// int main(void){
//     sei();
//     DDRB = 0x01 ; //Only pb1/trigger pin as output
//     initUsart();
//     initTimer1();
//     initTimer0();

//     char serialCharachter;
//     while(1){   
//       //serialCharachter = readValue() + '\n';
//       transmitByte(serialCharachter);
//       PORTB = serialCharachter;
//     }
// }

// ISR(TIMER0_OVF_vect)
// {
//     if(overflow_counter >= 14) overflow_counter =0;
//     else overflow_counter++;
// }





// //usart werkend maken en trigger ping sturen