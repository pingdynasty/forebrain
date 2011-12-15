#include "uafunc.h"
  
void setup() {
    LEDInit(ALL);               // Initialise LEDs
    HIDInit(1);                 // Initialise USB
}
  
void loop() {
  
}
  
void USBOut(unsigned char USBData[], unsigned int USBLength) {
    LEDWrite(USBData[0]);
}
  
void USBIn(unsigned char USBData[], unsigned int USBLength) {
 
}
