// #define true  1
// #define false 0

// #include <Arduino.h>
// #include <NeoSWSerial.h>

// NeoSWSerial SoftSerial (6,7);    //PB2 en 3 op atmega

// void setup() {
//   Serial.begin(9600);
//   Serial.println("Enter AT commands:");
//   SoftSerial.begin(9600);

// }

// void loop() {
//   // put your main code here, to run repeatedly:
//     if(SoftSerial.available())
//         Serial.write(SoftSerial.read());

//     if(Serial.available()){
//         SoftSerial.write(Serial.read());
//         //Serial.write(Serial.read());
//     }
//     SoftSerial.write("test");
//     // Serial.write("test");

//     _delay_ms(100);
// }


// Note M328P = MASTER MODE ZETTEN DAN WERKT CONNECTIE AUTOMATISCH