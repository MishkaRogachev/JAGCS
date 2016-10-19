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
    domain::MavLinkCommunicator* communicator;
};

ConnectionSettingsPresenter::ConnectionSettingsPresenter(
        domain::AbstractCommunicator* communicator, QObject* view):
    BasePresenter(view),
    d(new Impl())
{
    // FIXME: typecasting
    d->communicator = qobject_cast<domain::MavLinkCommunicator*>(communicator);
    Q_ASSERT(d->communicator);

    connect(d->communicator, &domain::MavLinkCommunicator::systemIdChanged,
            this, &ConnectionSettingsPresenter::updateSystemId);
    connect(d->communicator, &domain::MavLinkCommunicator::componentIdChanged,
            this, &ConnectionSettingsPresenter::updateComponentId);
    connect(d->communicator, &domain::MavLinkCommunicator::linksChanged,
            this, &ConnectionSettingsPresenter::updateLinks);

    connect(d->communicator, &domain::MavLinkCommunicator::addLinkEnabledChanged,
            view, [this] (bool addEnabled) {
        this->setViewProperty(PROPERTY(isAddEnabled), addEnabled);
    });
}

ConnectionSettingsPresenter::~ConnectionSettingsPresenter()
{
    delete d;
}

void ConnectionSettingsPresenter::connectView(QObject* view)
{
    connect(view, SIGNAL(requestSystemId(int)),
            this, SLOT(onSystemIdRequested(int)));
    connect(view, SIGNAL(requestComponentId(int)),
            this, SLOT(onComponentIdRequested(int)));
    connect(view, SIGNAL(requestNewUdp()), this, SLOT(onRequestNewUdp()));
    connect(view, SIGNAL(requestNewSerial()), this, SLOT(onRequestNewSerial()));
    connect(view, SIGNAL(requestRemoveLink(QObject*)),
            this, SLOT(onRequestRemoveLink(QObject*)));

    this->updateSystemId(d->communicator->systemId());
    this->updateComponentId(d->communicator->componentId());
    this->setViewProperty(PROPERTY(isAddEnabled),
                          d->communicator->isAddLinkEnabled());
    this->updateLinks();
    this->updateSerialDevices();
    this->updateSerialBaudRates();

    BasePresenter::connectView(view);
}

void ConnectionSettingsPresenter::updateSystemId(uint8_t systemId)
{
    this->setViewProperty(PROPERTY(systemId), systemId);
}

void ConnectionSettingsPresenter::updateComponentId(uint8_t componentId)
{
    this->setViewProperty(PROPERTY(componentId), componentId);
}

void ConnectionSettingsPresenter::updateLinks()
{
    QList<QObject*> links;

    for (domain::AbstractLink* link: d->communicator->links())
        links.append(link);

    this->setViewProperty(PROPERTY(links), QVariant::fromValue(links));
}

void ConnectionSettingsPresenter::updateSerialDevices()
{
    QStringList serialDevices;

    for (const QSerialPortInfo& info: QSerialPortInfo::availablePorts())
        serialDevices.append(info.portName());

    this->setViewProperty(PROPERTY(serialDevices), serialDevices);
}

void ConnectionSettingsPresenter::updateSerialBaudRates()
{
    QVariantList serialBaudRates;
    for (qint32 rate: QSerialPortInfo::standardBaudRates())
        serialBaudRates.append(rate);

    this->setViewProperty(PROPERTY(serialBaudRates), serialBaudRates);
}

void ConnectionSettingsPresenter::onSystemIdRequested(int systemId)
{
    if (systemId > 0 && systemId < 256) d->communicator->setSystemId(systemId);
}

void ConnectionSettingsPresenter::onComponentIdRequested(int componentId)
{
    if (componentId >= 0 && componentId < 256)
        d->communicator->setComponentId(componentId);
}

void ConnectionSettingsPresenter::onRequestNewUdp()
{
    domain::SettingsProvider::beginGroup(domain::connection_settings::group);

    auto link = new domain::UdpLink(
                    domain::SettingsProvider::value(
                        domain::connection_settings::hostPort).toInt(),
                    domain::SettingsProvider::value(
                        domain::connection_settings::address).toString(),
                    domain::SettingsProvider::value(
                        domain::connection_settings::port).toInt(),
                    d->communicator);
    link->setObjectName(tr("UDP"));

    domain::SettingsProvider::endGroup();

    d->communicator->addLink(link);
}

void ConnectionSettingsPresenter::onRequestNewSerial()
{
    domain::SettingsProvider::beginGroup(domain::connection_settings::group);

    auto link = new domain::SerialLink(
                    domain::SettingsProvider::value(
                        domain::connection_settings::serialDevice).toString(),
                    domain::SettingsProvider::value(
                        domain::connection_settings::baudRate).toInt(),
                    d->communicator);
    link->setObjectName(tr("Serial"));

    domain::SettingsProvider::endGroup();

    d->communicator->addLink(link);
}

void ConnectionSettingsPresenter::onRequestRemoveLink(QObject* link)
{
    d->communicator->removeLink(qobject_cast<domain::AbstractLink*>(link));
    delete link;
}
