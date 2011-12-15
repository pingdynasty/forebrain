#include "uafunc.h"
  
void setup() {
    ADCInit(ALL);               // Initialise all ADC pins
    HIDInit(1);                 // Initialise USB
}
  
void loop() {
  
}
  
void USBOut(unsigned char USBData[], unsigned int USBLength) {
     
}
  
void USBIn(unsigned char USBData[], unsigned int USBLength) {
    unsigned short value;
    value = ADCRead(CHN0);
    USBData[0] = HighByte(value);
    USBData[1] = LowByte(value);
    value = ADCRead(CHN1);
    USBData[2] = HighByte(value);
    USBData[3] = LowByte(value);
    value = ADCRead(CHN2);
    USBData[4] = HighByte(value);
    USBData[5] = LowByte(value);
    value = ADCRead(CHN3);
    USBData[6] = HighByte(value);
    USBData[7] = LowByte(value);
    value = ADCRead(CHN4);
    USBData[8] = HighByte(value);
    USBData[9] = LowByte(value);
    value = ADCRead(CHN5);
    USBData[10] = HighByte(value);
    USBData[11] = LowByte(value);
    value = ADCRead(CHN6);
    USBData[12] = HighByte(value);
    USBData[13] = LowByte(value);
    value = ADCRead(CHN7);
    USBData[14] = HighByte(value);
    USBData[15] = LowByte(value);
}
