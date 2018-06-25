#include "bluetooth_service.h"

// Qt
#include <QPointer>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QDebug>

// Internal
#include "notification_bus.h"

using namespace domain;

class BluetoothService::Impl
{
public:
    QPointer<QBluetoothDeviceDiscoveryAgent> agent;
    QList<QBluetoothDeviceInfo> devices;
};

BluetoothService::BluetoothService(QObject* parent):
    QObject(parent),
    d(new Impl())
{}

BluetoothService::~BluetoothService()
{
    this->stopDiscovery();
}

QStringList BluetoothService::devices() const
{
    QStringList list;

    for (const QBluetoothDeviceInfo& device: d->devices)
    {
        list.append(device.address().toString());
    }

    return list;
}

bool BluetoothService::isDiscoveryActive() const
{
    return d->agent && d->agent->isActive();
}

void BluetoothService::startDiscovery()
{
    if (d->agent) this->stopDiscovery();

    d->agent = new QBluetoothDeviceDiscoveryAgent(this);

    connect(d->agent, &QBluetoothDeviceDiscoveryAgent::finished,
            this, &BluetoothService::onStopped);
    connect(d->agent, &QBluetoothDeviceDiscoveryAgent::canceled,
            this, &BluetoothService::onStopped);

    connect(d->agent, &QBluetoothDeviceDiscoveryAgent::deviceDiscovered,
            this, [this](const QBluetoothDeviceInfo& info) {
        if (!info.isValid()) return;

        d->devices.append(info);
        emit deviceAdded(info.address().toString());
    });

    connect(d->agent, QOverload<QBluetoothDeviceDiscoveryAgent::Error>::of(
                &QBluetoothDeviceDiscoveryAgent::error), this, &BluetoothService::onEroor);

    d->agent->setInquiryType(QBluetoothDeviceDiscoveryAgent::GeneralUnlimitedInquiry);
    d->agent->start();
}

void BluetoothService::stopDiscovery()
{
    if (d->agent) d->agent->stop();
}

void BluetoothService::onStopped()
{
    d->agent->deleteLater();

    emit stopped();
}

void BluetoothService::onEroor(int error)
{
    switch (error)
    {
    case QBluetoothDeviceDiscoveryAgent::NoError:
        break;
    case QBluetoothDeviceDiscoveryAgent::PoweredOffError:
        notificationBus->notify(tr("Bluetooth service"),
                                tr("The Bluetooth adaptor is powered off"),
                                dto::Notification::Warning);
        break;
    case QBluetoothDeviceDiscoveryAgent::InputOutputError:
        notificationBus->notify(tr("Bluetooth service"),
                                tr("Writing or reading from the device resulted in an error"),
                                dto::Notification::Warning);
        break;
    case QBluetoothDeviceDiscoveryAgent::InvalidBluetoothAdapterError:
        notificationBus->notify(tr("Bluetooth service"),
                                tr("The passed local adapter address does not match the "
                                   "physical adapter address of any local Bluetooth device"),
                                dto::Notification::Warning);
        break;
    case QBluetoothDeviceDiscoveryAgent::UnsupportedPlatformError:
        notificationBus->notify(tr("Bluetooth service"),
                                tr("Device discovery is not possible or implemented "
                                   "on the current platform"),
                                dto::Notification::Warning);
        break;
    case QBluetoothDeviceDiscoveryAgent::UnsupportedDiscoveryMethod:
        notificationBus->notify(tr("Bluetooth service"),
                                tr("One of the requested discovery methods is "
                                   "not supported by the current platform"),
                                dto::Notification::Warning);
    default:
    case QBluetoothDeviceDiscoveryAgent::UnknownError:
        notificationBus->notify(tr("Bluetooth service"),
                                tr("An unknown error has occurred"),
                                dto::Notification::Warning);
        break;
    }
}
