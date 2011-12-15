#ifndef HIDDEVICE_H
#define HIDDEVICE_H

#include <QtGui>

#include "hidapi.h"

#define USBIN_BYTES     64
#define USBOUT_BYTES    64

#define USE_SIMULATION  0   // Set to 0 to use USB
                            // Set to 1 to use random jumps
                            // Set to 2 to use add noise to a value

class hidDevice : public QObject { Q_OBJECT
public:
    hidDevice(unsigned short vidLocal, unsigned short pidLocal);
    ~hidDevice();

public slots:
    void sendData(unsigned char * data);
    void changeDevice(unsigned short vidLocal, unsigned short pidLocal);
    void connectHID();
    void disconnectHID();

private slots:
    void readData(void);

signals:
    void connStatus(QString value);
    void disconnectSignal();
    void connectSignal();
    void receiveData(unsigned char * data);

private:
    hid_device *hidHandle;
    QTimer *timer;
    unsigned short vid;
    unsigned short pid;
    bool lastStatus;
};



#endif // HIDDEVICE_H
