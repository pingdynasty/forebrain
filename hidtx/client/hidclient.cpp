#include <iostream>
#include <unistd.h>
#include "hidapi.h"

#include <iostream>
#include <fstream>
#include <ctime>
#include "hidapi.h"
 
#define VENDOR_ID   0x1fc9
#define DEVICE_ID   0x0003
 
using namespace std;
 
int main(int argc, char *argv[]) {
  unsigned char USBDataBuffer[65];
  hid_device *USBHandle;
  int USBResult;
//   time_t startTime;
//   ofstream logFile;
 
  cout << "Forebrain USB HID Project" << endl;
 
  //     // *** Check for a logfile in the argument
  //     if(argc > 1) {
  //         logFile.open(argv[1], ios::app);
  //     }
  //     else {
  //         logFile.open("fbr_log.txt", ios::app);
  //     }
 
  // *** If the file gets opened
  //     if(logFile.is_open()) {
  cout << "Press ctlr-c to quit" << endl;
  USBHandle = NULL;
 
  // Handle the escape keypress
//   while (!GetAsyncKeyState(VK_ESCAPE)) {
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
	//                     logFile << "Device disconnected" << endl;
	USBHandle = NULL;
      }
      // otherwise no data, don't do anything special, check again later
      usleep(1000);
 
 
 
    }
    else {
 
 
 
      // if not connected, attempt to connect
      USBHandle = hid_open(VENDOR_ID, DEVICE_ID, NULL);    // attempt to open device
 
      // check handle
      if(USBHandle) {
	// if handle is set, then connection has been made
	hid_set_nonblocking(USBHandle, 1);                // set hid_read() in non-blocking mode
	cout << "Device connected" << endl;
 
	// open file
	//                     time(&startTime);
	//                     tm *dateTime = localtime(&startTime);
	//                     logFile << endl << "Logfile started: " << asctime(dateTime);
      }
      else {
	// otherwise wait for device
	usleep(10000);
      }
 
    }
  }
 
  // end file
  //         time(&startTime);
  //         tm *dateTime = localtime(&startTime);
  //         logFile << endl << "Logging ended: " << asctime(dateTime);
  //         logFile.close();
 
  // close USB
  if(USBHandle) hid_close(USBHandle);
  //     }
//     else {
//         cerr << "Could not open logfile" << endl;
//     }
 
    return 0;
} 
