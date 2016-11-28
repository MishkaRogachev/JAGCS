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
using namespace domain;

class ConnectionSettingsPresenter::Impl
{
public:
    MavLinkCommunicator* communicator;
};

ConnectionSettingsPresenter::ConnectionSettingsPresenter(
        AbstractCommunicator* communicator, QObject* parent):
    BasePresenter(parent),
    d(new Impl())
{
    // FIXME: typecasting
    d->communicator = qobject_cast<MavLinkCommunicator*>(communicator);
    Q_ASSERT(d->communicator);

    connect(d->communicator, &MavLinkCommunicator::systemIdChanged,
            this, &ConnectionSettingsPresenter::updateSystemId);
    connect(d->communicator, &MavLinkCommunicator::componentIdChanged,
            this, &ConnectionSettingsPresenter::updateComponentId);
    connect(d->communicator, &MavLinkCommunicator::linksChanged,
            this, &ConnectionSettingsPresenter::updateLinks);
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
    connect(d->communicator, &MavLinkCommunicator::addLinkEnabledChanged,
            view, [this] (bool addEnabled) {
        this->setViewProperty(PROPERTY(isAddEnabled), addEnabled);
    });

    this->updateSystemId(d->communicator->systemId());
    this->updateComponentId(d->communicator->componentId());
    this->setViewProperty(PROPERTY(isAddEnabled),
                          d->communicator->isAddLinkEnabled());
    this->updateLinks();
    this->updateSerialDevices();
    this->updateSerialBaudRates();
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

    for (AbstractLink* link: d->communicator->links())
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
    SettingsProvider::beginGroup(connection_settings::group);

    auto link = new UdpLink(SettingsProvider::value(
                                connection_settings::port).toInt(),
                            d->communicator);
    link->setObjectName(tr("UDP"));

    SettingsProvider::endGroup();

    d->communicator->addLink(link);
}

void ConnectionSettingsPresenter::onRequestNewSerial()
{
    SettingsProvider::beginGroup(connection_settings::group);

    auto link = new SerialLink(SettingsProvider::value(
                                   connection_settings::serialDevice).toString(),
                               SettingsProvider::value(
                                   connection_settings::baudRate).toInt(),
                               d->communicator);
    link->setObjectName(tr("Serial"));

    SettingsProvider::endGroup();

    d->communicator->addLink(link);
}

void ConnectionSettingsPresenter::onRequestRemoveLink(QObject* link)
{
    d->communicator->removeLink(qobject_cast<AbstractLink*>(link));
    delete link;
}
