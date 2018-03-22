#include "link_edit_presenter.h"

// Qt
#include <QMap>
#include <QVariant>
#include <QDebug>

// Internal
#include "link_description.h"
#include "link_statistics.h"

#include "service_registry.h"
#include "serial_ports_service.h"
#include "communication_service.h"

#include "link_statistics_model.h"

namespace
{
    const QString separator = ",";
}

using namespace presentation;

LinkEditPresenter::LinkEditPresenter(QObject* parent):
    LinkPresenter(parent),
    m_serialService(serviceRegistry->serialPortService()),
    m_statisticsModel(new LinkStatisticsModel(this))
{
    connect(m_serialService, &domain::SerialPortService::availableDevicesChanged,
            this, &LinkEditPresenter::updateDevices);
}

void LinkEditPresenter::setLink(int id)
{
    m_description = m_service->description(id);

    this->updateDevices();
    this->updateLink();
    this->updateStatus();
}

void LinkEditPresenter::updateLink()
{
    if (m_description.isNull()) return;

    LinkPresenter::updateLink();

    this->setViewProperty(PROPERTY(port), m_description->parameter(dto::LinkDescription::Port));
    this->setViewProperty(PROPERTY(device), m_description->parameter(dto::LinkDescription::Device));
    this->setViewProperty(PROPERTY(baudRate),
                          m_description->parameter(dto::LinkDescription::BaudRate));
    QString endpoints = m_description->parameter(dto::LinkDescription::Endpoints).toString();
    this->setViewProperty(PROPERTY(endpoints), endpoints.isEmpty() ?
                              QStringList() : endpoints.split(::separator));
    this->setViewProperty(PROPERTY(autoResponse),
                          m_description->parameter(dto::LinkDescription::UdpAutoResponse));

    this->setViewProperty(PROPERTY(changed), false);
}

void LinkEditPresenter::updateRates()
{
    QVariantList baudRates;
    for (qint32 rate: domain::SerialPortService::availableBaudRates()) baudRates.append(rate);
    this->setViewProperty(PROPERTY(baudRates), baudRates);
}

void LinkEditPresenter::updateDevices()
{
    QStringList devices;
    devices.append(QString());

    for (const QString& device: m_serialService->availableDevices())
    {
        devices.append(device);
    }

    QString device = m_description->parameter(dto::LinkDescription::Device).toString();
    if (m_description && !devices.contains(device))
    {
        devices.append(device);
    }

    this->setViewProperty(PROPERTY(devices), devices);
}

void LinkEditPresenter::save()
{
    if (m_description.isNull()) return;

    m_description->setName(this->viewProperty(PROPERTY(name)).toString());
    m_description->setParameter(dto::LinkDescription::Device,
                                this->viewProperty(PROPERTY(device)).toString());
    m_description->setParameter(dto::LinkDescription::BaudRate,
                                this->viewProperty(PROPERTY(baudRate)).toInt());
    m_description->setParameter(dto::LinkDescription::Port,
                                this->viewProperty(PROPERTY(port)).toInt());

    QStringList endpoints = this->viewProperty(PROPERTY(endpoints)).toStringList();
    endpoints = endpoints.toSet().toList(); // remove dublicates
    this->setViewProperty(PROPERTY(endpoints), endpoints);
    m_description->setParameter(dto::LinkDescription::Endpoints, endpoints.join(::separator));
    m_description->setParameter(dto::LinkDescription::UdpAutoResponse,
                                this->viewProperty(PROPERTY(autoResponse)).toBool());

    if (!m_service->save(m_description)) return;

    this->setViewProperty(PROPERTY(changed), false);
}

void LinkEditPresenter::connectView(QObject* view)
{
    view->setProperty(PROPERTY(statistics), QVariant::fromValue(m_statisticsModel));
}

void LinkEditPresenter::updateStatistics(const dto::LinkStatisticsPtr& statistics)
{
    m_statisticsModel->addData(statistics);

    // don't call LinkPresenter's impl
}
