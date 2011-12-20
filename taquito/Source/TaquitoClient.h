#ifndef __TAQUITO_CLIENT__
#define __TAQUITO_CLIENT__

#include <inttypes.h>
#include "hidapi.h"

#define TAQUITO_PARAMETERS 8

class TaquitoClient {
public:
  TaquitoClient();
  void connect();
  void disconnect();
  void read();
  uint16_t data[TAQUITO_PARAMETERS];
private:
  hid_device *USBHandle;
};

#endif /* __TAQUITO_CLIENT__ */
