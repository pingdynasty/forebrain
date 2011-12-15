#include <iostream>
#include <unistd.h>
#include <signal.h>
#include "hidapi.h"
 
#define VENDOR_ID   0x1fc9
#define DEVICE_ID   0x0003
 
using namespace std;
 
hid_device *USBHandle;

void sighandler(int sig){
  cerr << endl << "closing USB connection" << endl;
  cout << "." << endl;
  // close USB
  if(USBHandle) 
    hid_close(USBHandle);
  exit(0);
}

int main(int argc, char *argv[]) {
  unsigned char USBDataBuffer[65];
  int USBResult;

  signal(SIGINT, &sighandler);
  USBHandle = NULL;
 
  cerr << "Forebrain USB HID Project" << endl;
  cerr << "Press ctlr-c to quit" << endl;
 
  for(;;){
    // check USB connection, receive data or try to connect
    if (USBHandle) {
 
      // read some data
      USBResult = hid_read(USBHandle, USBDataBuffer, sizeof(USBDataBuffer));
 
      // check for a result
      if (USBResult > 0) {    // if result is bigger than zero, then it's data
	cerr << ".";
 
	// print data on std out
	for(int i=0; i<16; i+= 2) {
	  cout << (int)(USBDataBuffer[i] << 8 | USBDataBuffer[i+1]) << ",";
	}
	cout << endl;
      }
      else if(USBResult < 0) {
	// if result is smaller than zero, then it's an error, so disconnect
	cerr << "Device disconnected" << endl;
	USBHandle = NULL;
      }
      // otherwise no data, don't do anything special, check again later
      usleep(1000);
 
    } else {
      // if not connected, attempt to connect
      USBHandle = hid_open(VENDOR_ID, DEVICE_ID, NULL);    // attempt to open device
 
      // check handle
      if(USBHandle) {
	// if handle is set, then connection has been made
	hid_set_nonblocking(USBHandle, 1);                // set hid_read() in non-blocking mode
	cerr << "Device connected" << endl;
      }
      else {
	// otherwise wait for device
	usleep(10000);
      }
 
    }
  }
  return -1;
} 
