#include "serial_device_pool.h"

// Qt
#include <QMap>
#include <QMutexLocker>
#include <QDebug>

// FIXME: to comm thread
// Internal
#include "serial_link.h"

using namespace data_source;

class SerialDevicePool::Impl
{
public:
    QStringList availableDevices;
    QMap<SerialLink*, QString> busyDevices;

    QMutex mutex;

    Impl():
        mutex(QMutex::Recursive)
    {}
};

SerialDevicePool::SerialDevicePool(QObject* parent):
    QObject(parent),
    d(new Impl())
{}

SerialDevicePool::~SerialDevicePool()
{}

QStringList SerialDevicePool::allDevices() const
{
    return this->availableDevices() + this->busyDevices();
}

QStringList SerialDevicePool::busyDevices() const
{
    QMutexLocker locker(&d->mutex);
    return d->busyDevices.values();
}

QStringList SerialDevicePool::availableDevices() const
{
    QMutexLocker locker(&d->mutex);
    return d->availableDevices;
}

void SerialDevicePool::setDiscoveredDevices(const QStringList& newDevices)
{
    QMutexLocker locker(&d->mutex);

    bool changed = false;
    for (const QString& availableDevice: d->availableDevices)
    {
        if (newDevices.contains(availableDevice)) continue;

        d->availableDevices.removeOne(availableDevice);
        changed = true;
    }

    for (const QString& newDevice: newDevices)
    {
        if (d->availableDevices.contains(newDevice)) continue;

        d->availableDevices.append(newDevice);
        changed = true;

        if (SerialLink* link = d->busyDevices.key(newDevice))
        {
            if (!link->isConnected()) link->setConnected(true);
        }
    }

    if (changed) emit devicesChanged();
}

void SerialDevicePool::updateLink(SerialLink* link)
{
    QMutexLocker locker(&d->mutex);

    if (d->busyDevices.value(link) == link->device()) return;

    if (link->device().isEmpty())
    {
        this->removeLink(link);
    }
    else
    {
        d->busyDevices[link] = link->device();
        emit devicesChanged();
    }
}

void SerialDevicePool::removeLink(SerialLink* link)
{
    QMutexLocker locker(&d->mutex);

    if (d->busyDevices.remove(link)) emit devicesChanged();
}
