#ifndef SERIAL_DEVICE_POOL_TEST_H
#define SERIAL_DEVICE_POOL_TEST_H

#include <QTest>

class SerialDevicePoolTest: public QObject
{
    Q_OBJECT

private slots:
    void testAvailableDevices();
};

#endif // SERIAL_DEVICE_POOL_TEST_H
