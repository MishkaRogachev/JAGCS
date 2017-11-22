#include "communication_link_presenter.h"

// Qt
#include <QMap>
#include <QVariant>
#include <QDebug>

// Internal
#include "service_registry.h"
#include "serial_ports_service.h"
#include "communication_service.h"
#include "link_description.h"

using namespace presentation;

CommunicationLinkPresenter::CommunicationLinkPresenter(QObject* parent):
    BasePresenter(parent),
    m_serialPortsService(domain::ServiceRegistry::serialPortService()),
    m_commService(domain::ServiceRegistry::communicationService())
{
    connect(m_serialPortsService, &domain::SerialPortService::availableDevicesChanged,
            this, &CommunicationLinkPresenter::updateDevices);

    connect(m_commService, &domain::CommunicationService::descriptionChanged, this,
            [this](const dao::LinkDescriptionPtr& description) {
        if (m_description == description) this->updateLink();
    });
    connect(m_commService, &domain::CommunicationService::linkStatisticsChanged, this,
            [this](const dao::LinkDescriptionPtr& description) {
        if (m_description == description) this->updateStatistics();
    });
}

void CommunicationLinkPresenter::setLink(int id)
{
    m_description = m_commService->description(id);

    this->updateDevices();
    this->updateLink();
    this->updateStatistics();
}

void CommunicationLinkPresenter::updateRates()
{
    QVariantList baudRates;
    for (qint32 rate: domain::SerialPortService::availableBaudRates()) baudRates.append(rate);
    this->setViewProperty(PROPERTY(baudRates), baudRates);
}

void CommunicationLinkPresenter::updateLink()
{
    this->setViewProperty(PROPERTY(type), m_description ? m_description->type() :
                                                          dao::LinkDescription::UnknownType);
    this->setViewProperty(PROPERTY(name), m_description ? m_description->name() : QString());
    this->setViewProperty(PROPERTY(port), m_description ? m_description->port() : 0);
    this->setViewProperty(PROPERTY(device), m_description ? m_description->device() : QString());
    this->setViewProperty(PROPERTY(baudRate), m_description ? m_description->baudRate() : 0);

    this->setViewProperty(PROPERTY(changed), false);
}

void CommunicationLinkPresenter::updateStatistics()
{
    this->setViewProperty(PROPERTY(connected), m_description && m_description->isConnected());
    this->setViewProperty(PROPERTY(protocol), m_description ? m_description->protocol() :
                                                              dao::LinkDescription::UnknownProtocol);
    this->setViewProperty(PROPERTY(bytesSent), m_description ?
                              QVariant::fromValue(m_description->bytesSent()) : QVariant());
    this->setViewProperty(PROPERTY(bytesRecv), m_description ?
                              QVariant::fromValue(m_description->bytesRecv()) : QVariant());
}

void CommunicationLinkPresenter::updateDevices()
{
    QStringList devices;
    devices.append(QString());

    for (const QString& device: m_serialPortsService->availableDevices())
    {
        devices.append(device);
    }

    if (m_description && !devices.contains(m_description->device()))
    {
        devices.append(m_description->device());
    }

    this->setViewProperty(PROPERTY(devices), devices);
}

void CommunicationLinkPresenter::setConnected(bool connected)
{
    if (m_description.isNull()) return;

    m_commService->setLinkConnected(m_description, connected);
}

void CommunicationLinkPresenter::save()
{
    if (m_description.isNull()) return;

    m_description->setName(this->viewProperty(PROPERTY(name)).toString());
    m_description->setPort(this->viewProperty(PROPERTY(port)).toInt());
    m_description->setDevice(this->viewProperty(PROPERTY(device)).toString());
    m_description->setBaudRate(this->viewProperty(PROPERTY(baudRate)).toInt());

    if (!m_commService->save(m_description)) return;

    this->setViewProperty(PROPERTY(changed), false);
}

void CommunicationLinkPresenter::remove()
{
    if (m_description.isNull()) return;

    m_commService->remove(m_description);
}
