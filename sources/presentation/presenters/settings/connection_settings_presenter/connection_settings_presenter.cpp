#include "connection_settings_presenter.h"

// Internal
#include "settings_provider.h"
#include "settings.h"

#include "abstract_communicator.h"
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
    domain::AbstractCommunicator* communicator;
};

ConnectionSettingsPresenter::ConnectionSettingsPresenter(
        domain::SettingsProvider* settings,
        domain::AbstractCommunicator* communicator,
        QObject* view):
    BasePresenter(view),
    d(new Impl())
{
    d->settings = settings;
    d->communicator = communicator;

    connect(d->communicator, &domain::AbstractCommunicator::addEnabledChanged,
            this, &ConnectionSettingsPresenter::addEnabledChanged);
    connect(d->communicator, &domain::AbstractCommunicator::linksChanged,
            this, &ConnectionSettingsPresenter::onCommunicatorLinksChanged);
}

ConnectionSettingsPresenter::~ConnectionSettingsPresenter()
{
    delete d;
}

bool ConnectionSettingsPresenter::isAddEnabled() const
{
    return d->communicator->isAddEnabled();
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

void ConnectionSettingsPresenter::addSerialLink()
{
    d->settings->beginGroup(domain::connection_settings::group);

    auto link = new domain::SerialLink(
                    d->settings->value(domain::connection_settings::serialDevice).toString(),
                    d->settings->value(domain::connection_settings::baudRate).toInt());
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
                    d->settings->value(domain::connection_settings::port).toInt());
    link->setObjectName(tr("UDP"));

    d->settings->endGroup();

    d->communicator->addLink(link);
}

void ConnectionSettingsPresenter::removeLink(QObject* link)
{
    d->communicator->removeLink(qobject_cast<domain::AbstractLink*>(link));
    delete link;
}

void ConnectionSettingsPresenter::onCommunicatorLinksChanged()
{
    emit linksChanged(this->links());
}
