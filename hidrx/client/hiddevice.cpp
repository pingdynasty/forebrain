#include "hiddevice.h"

hidDevice::hidDevice(unsigned short vidLocal, unsigned short pidLocal) {
    changeDevice(vidLocal, pidLocal);
    timer = new QTimer(this);
    lastStatus = false;
    hidHandle = NULL;
    timer->start(100);
    connect(timer, SIGNAL(timeout()), this, SLOT(readData()));
}

hidDevice::~hidDevice() {
    disconnectHID();
}

void hidDevice::connectHID(void) {
    // Connect to device
    hidHandle = hid_open(vid, pid, NULL);	// open device Vendor ID 0x1fc9, Device ID 0x0003, no serial number
    if (!hidHandle) {
        if(lastStatus == true) { // avoids continuously sending "Disconnected"
            emit connStatus("Disconnected");
            emit disconnectSignal();
        }
        timer->setInterval(100); // set timer to 100 mS (timerEvent will try to reconnect at 100mS
        lastStatus = false;
    }
    else {
        emit connStatus("Connected");
        hid_set_nonblocking(hidHandle, 1);   // set hid_read() in non-blocking mode
        timer->setInterval(1);                          // set timer to 1mS to read data at max rate
        emit connectSignal();
        lastStatus = true;
    }
}

void hidDevice::disconnectHID(void) {
    if(hidHandle) {
        hid_close(hidHandle);
        emit connStatus("Closed by user");
        emit disconnectSignal();
    }
}

void hidDevice::changeDevice(unsigned short vidLocal, unsigned short pidLocal){
    vid = vidLocal;
    pid = pidLocal;
}

void hidDevice::readData(void) {
    unsigned char buffer[64];
    int length;

    if(hidHandle) {                             // if USB is connected, read data
        length = hid_read(hidHandle, buffer, (USBIN_BYTES+1));	// read some data
        if(length > 0) {        // when length is greater than zero, emit the signal
            emit receiveData(buffer);
        }
        else if(length < 0) {   // this is a read error, this usually means a disconnected device
            hidHandle = NULL;
        }
    }
    else {                                      // otherwise try to reconnect
        connectHID();  // try to reconnect
    }

}

void hidDevice::sendData(unsigned char * data) {
    unsigned char buffer[USBOUT_BYTES+1], i;

    buffer[0] = 0;    // data[0] MUST be zero, this is the report indicator, since the USB HID ROM only uses on report, this must be zero
    for(i=0; i<USBOUT_BYTES; i++) {
        buffer[i+1] = data[i];
    }

    if (hidHandle) {
        hid_write(hidHandle, buffer, (USBOUT_BYTES+1));
    }
}

