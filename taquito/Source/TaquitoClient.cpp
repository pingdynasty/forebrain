#include "TaquitoClient.h"
#include "hidapi.h"
#include <string.h>
#include <iostream>

#define VENDOR_ID   0x1fc9
#define DEVICE_ID   0x0003

class TaquitoError {};

TaquitoClient::TaquitoClient() : 
  USBHandle(NULL) {
  memset(data, 0, sizeof(data));
//   if(!hid_init()){
//     throw TaquitoError();
//   }
}

void TaquitoClient::connect(){
  std::cerr << "connecting" << std::endl;
  if(USBHandle) 
    disconnect();
  USBHandle = hid_open(VENDOR_ID, DEVICE_ID, NULL);    // attempt to open device
  if(USBHandle) {
    // if handle is set, then connection has been made
    hid_set_nonblocking(USBHandle, 1);                // set hid_read() in non-blocking mode
  }else{
    std::cerr << "connection failure" << std::endl;
    throw TaquitoError();
  }
}

void TaquitoClient::disconnect(){
  std::cerr << "disconnecting" << std::endl;
  if(USBHandle) 
    hid_close(USBHandle);
  USBHandle = NULL;
}

void TaquitoClient::read(){
//   std::cout << "reading" << std::endl;
  if(USBHandle == NULL)
    return;
  unsigned char buf[sizeof(data)*2];
  memset(buf, 0, sizeof(buf));
  int res = hid_read(USBHandle, buf, sizeof(buf));
  if(res > 0){
    // if result is bigger than zero, then it's data
    // print data on std out
    for(int i=0; i<sizeof(data); ++i)
      data[i] = (buf[i*2] << 8) | buf[i*2+1];
  }else if(res < 0){
    // if result is smaller than zero, then it's an error, so disconnect
    USBHandle = NULL;
    std::cerr << "read error" << std::endl;
    throw TaquitoError();
  }
}
