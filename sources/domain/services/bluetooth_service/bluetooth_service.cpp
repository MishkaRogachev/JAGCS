#include "bluetooth_service.h"

// Qt
#include <QBluetoothDeviceDiscoveryAgent>
#include <QDebug>

// Internal
#include "notification_bus.h"

using namespace domain;

class BluetoothService::Impl
{
public:
    QBluetoothDeviceDiscoveryAgent* agent = nullptr;

    QList<QBluetoothDeviceInfo> devices;
};

BluetoothService::BluetoothService(QObject* parent):
    QObject(parent),
    d(new Impl())
{
    d->agent = new QBluetoothDeviceDiscoveryAgent(this);

    connect(d->agent, &QBluetoothDeviceDiscoveryAgent::finished,
            this, &BluetoothService::stopped);
    connect(d->agent, &QBluetoothDeviceDiscoveryAgent::canceled,
            this, &BluetoothService::stopped);

    connect(d->agent, &QBluetoothDeviceDiscoveryAgent::deviceDiscovered,
            this, [this](const QBluetoothDeviceInfo& info) {
        d->devices.append(info);
        emit deviceAdded(info.address().toString());
    });

    connect(d->agent,
            QOverload<QBluetoothDeviceDiscoveryAgent::Error>::of(&QBluetoothDeviceDiscoveryAgent::error),
            this, [this](QBluetoothDeviceDiscoveryAgent::Error error) {
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
    });

}

BluetoothService::~BluetoothService()
{}

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
    return d->agent->isActive();
}

void BluetoothService::startDiscovery()
{
    d->agent->start();
}

void BluetoothService::stopDiscovery()
{
    d->agent->stop();
}
