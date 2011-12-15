#include <iostream>
#include <unistd.h>
#include "hidapi.h"
 
#define VENDOR_ID   0x1fc9
#define DEVICE_ID   0x0003
#define OUT_SIZE    64
#define IN_SIZE     64
 
using namespace std;
 
int main(int argc, char *argv[]) {
    unsigned char USBOutBuffer[OUT_SIZE+1] = {0};
    hid_device *USBHandle;
 
    // attempt to open device
    USBHandle = hid_open(VENDOR_ID, DEVICE_ID, NULL);
 
    // check the device was opened
    if(USBHandle) {
        cout << "Device connected" << endl;
 
        // send 16 numbers
        for(int i=0; i<16; i++) {
            USBOutBuffer[0] = 0;  // First byte must be zero! This is the the report ID, which is zero.
            USBOutBuffer[1] = i;  // This is the actual data byte being sent
            hid_write(USBHandle, USBOutBuffer, sizeof(USBOutBuffer)); // send the data
 
            cout << "Sending " << i << "..." << endl;
 
            usleep(500000);
        }
 
        cout << "Finished." << endl;
 
        // close USB
        if(USBHandle) hid_close(USBHandle);
    }
    else {
        cout << "No device found" << endl;
    }
 
    return 0;
}
