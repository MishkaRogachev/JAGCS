#include "connection_settings_presenter.h"

// Internal
#include "settings_provider.h"
#include "settings.h"

#include "mavlink_communicator.h"
#include "serial_link.h"
#include "udp_link.h"

// Qt
#include <QSerialPortInfo>
#include <QDebug>

using namespace presentation;

class ConnectionSettingsPresenter::Impl
{
public:
    domain::SettingsProvider* settings;
    domain::MavLinkCommunicator* communicator;
};

ConnectionSettingsPresenter::ConnectionSettingsPresenter(
        domain::SettingsProvider* settings,
        domain::AbstractCommunicator* communicator,
        QObject* view):
    BasePresenter(view),
    d(new Impl())
{
    d->settings = settings;

    // FIXME: typecasting
    d->communicator = qobject_cast<domain::MavLinkCommunicator*>(communicator);
    Q_ASSERT(d->communicator);

    connect(d->communicator, &domain::MavLinkCommunicator::systemIdChanged,
            this, &ConnectionSettingsPresenter::systemIdChanged);
    connect(d->communicator, &domain::MavLinkCommunicator::componentIdChanged,
            this, &ConnectionSettingsPresenter::componentIdChanged);

    connect(communicator, &domain::AbstractCommunicator::addLinkEnabledChanged,
            this, &ConnectionSettingsPresenter::addEnabledChanged);
    connect(communicator, &domain::AbstractCommunicator::linksChanged,
            this, &ConnectionSettingsPresenter::linksChanged);
}

ConnectionSettingsPresenter::~ConnectionSettingsPresenter()
{
    delete d;
}

int ConnectionSettingsPresenter::systemId() const
{
    return d->communicator->systemId();
}

int ConnectionSettingsPresenter::componentId() const
{
    return d->communicator->componentId();
}


bool ConnectionSettingsPresenter::isAddEnabled() const
{
    return d->communicator->isAddLinkEnabled();
}

QList<QObject*> ConnectionSettingsPresenter::links() const
{
    QList<QObject*> list;

    for (domain::AbstractLink* link: d->communicator->links())
        list.append(link);

    return list;
}

QStringList ConnectionSettingsPresenter::serialDevices() const
{
    QStringList devices;

    for (const QSerialPortInfo& info: QSerialPortInfo::availablePorts())
        devices.append(info.portName());

    return devices;
}

QVariantList ConnectionSettingsPresenter::serialBaudRates() const
{
    QVariantList rates;
    for (qint32 rate: QSerialPortInfo::standardBaudRates())
        rates.append(rate);

    return rates;
}

void ConnectionSettingsPresenter::setSystemId(int systemId)
{
    d->communicator->setSystemId(systemId);
}

void ConnectionSettingsPresenter::setComponentId(int componentId)
{
    d->communicator->setComponentId(componentId);
}

void ConnectionSettingsPresenter::addSerialLink()
{
    d->settings->beginGroup(domain::connection_settings::group);

    auto link = new domain::SerialLink(
                    d->settings->value(domain::connection_settings::serialDevice).toString(),
                    d->settings->value(domain::connection_settings::baudRate).toInt(),
                    d->communicator);
    link->setObjectName(tr("Serial"));

    d->settings->endGroup();

    d->communicator->addLink(link);
}

void ConnectionSettingsPresenter::addUdpLink()
{
    d->settings->beginGroup(domain::connection_settings::group);

    auto link = new domain::UdpLink(
                    d->settings->value(domain::connection_settings::hostPort).toInt(),
                    d->settings->value(domain::connection_settings::address).toString(),
                    d->settings->value(domain::connection_settings::port).toInt(),
                    d->communicator);
    link->setObjectName(tr("UDP"));

    d->settings->endGroup();

    d->communicator->addLink(link);
}

void ConnectionSettingsPresenter::removeLink(QObject* link)
{
    d->communicator->removeLink(qobject_cast<domain::AbstractLink*>(link));
    delete link;
}

