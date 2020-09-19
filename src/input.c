// /*
//  * input.c
//  *
//  *  Created on: May 23, 2020
//  *      Author: zep
//  *  Description:
//  *  Simple program to read input from a button connected to the avr
//  */
// #ifndef BAUD
// #define BAUD 9600
// #endif

// #define DEBOUNCE_TIME 1000

// #include <avr/io.h>
// #include <util/delay.h>
// #include <util/setbaud.h>
// #include <stdio.h>
// #include <stdlib.h>


// void initUsart(){
// 	UCSR0B |= (1<<TXEN0) | (1<<RXEN0);
// 	UCSR0C |= (1<<UCSZ00) | (1<<UCSZ01); //8 bit character size
// 	UBRR0H = UBRRH_VALUE;
// 	UBRR0L = UBRRL_VALUE;
// }
// void transmitByte(uint8_t data){
//   //while(UCSR0A | UDRE0){}
//   loop_until_bit_is_set(UCSR0A, UDRE0);
//   UDR0 = data;
// }

// uint8_t receiveByte(){
//   //while(UCSR0A | RXC0){}
//   loop_until_bit_is_set(UCSR0A,RXC0);
//   return UDR0;
// }
// uint8_t debounce()
// {
//     //If pd2 is high even after delay time, then its not a bounce but a user button press
//     if(!(PIND & (1 << PD2))){
//         _delay_us(DEBOUNCE_TIME);
//         if(!(PIND & (1 << PD2))){
//             return 1;
//         }
//     }
//     return 0;
// }

// int main(){
//     uint8_t buttonWasPressed;
//     int countButtonPresses = 1;
//     char buffer[5] = {'\n'}; //Makes sures memory location is empty if not done then random characters in usart transfer
    
//     PORTD |= (1 << PD2); //Enable pull-up resistor
//     DDRB  |= (1 << PB0); //Led as output
 
//     initUsart();
    
//     while(1){
//         if(debounce()){
//             if(buttonWasPressed == 0){
//                 PORTB ^= (1 << PB0);        //Togle output signal of pb0
//                 buttonWasPressed = 1;
//                 itoa(countButtonPresses++, buffer, 10); //Convert int char array
//                 for(int i = 0; i < sizeof(buffer); i++){ //Loop through buffer and send
//                     if(buffer[i] == '\0')                  //Break loop when end of char array is reached
//                         break;
//                     transmitByte(buffer[i]);
//                 }

//             }
//         }else
//             buttonWasPressed = 0;
//     }
//     return 0;
// }












