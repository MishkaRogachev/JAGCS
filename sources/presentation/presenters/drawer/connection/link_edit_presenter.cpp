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
    m_link = m_service->description(id);

    // TODO: read old statistics
    m_statisticsModel->resetData(dto::LinkStatisticsPtrList());

    this->updateDevices();
    this->updateLink();
    this->updateStatus();
}

void LinkEditPresenter::updateLink()
{
    LinkPresenter::updateLink();

    this->setViewProperty(PROPERTY(port),
                          m_link ? m_link->parameter(dto::LinkDescription::Port) : 0);
    this->setViewProperty(PROPERTY(device),
                          m_link ? m_link->parameter(dto::LinkDescription::Device) : QString());
    this->setViewProperty(PROPERTY(baudRate),
                          m_link ? m_link->parameter(dto::LinkDescription::BaudRate) : 0);
    QString endpoints;
    if (m_link) endpoints = m_link->parameter(dto::LinkDescription::Endpoints).toString();
    this->setViewProperty(PROPERTY(endpoints), endpoints.isEmpty() ?
                              QStringList() : endpoints.split(::separator));
    this->setViewProperty(PROPERTY(autoResponse),
                          m_link ? m_link->parameter(dto::LinkDescription::UdpAutoResponse) : false);

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
    if (!this->view()) return;

    QStringList devices;
    devices.append(QString());

    for (const QString& device: m_serialService->availableDevices())
    {
        devices.append(device);
    }

    if (m_link)
    {
        QString device = m_link->parameter(dto::LinkDescription::Device).toString();
        if (m_link && !devices.contains(device))
        {
            devices.append(device);
        }
    }

    this->setViewProperty(PROPERTY(devices), devices);
}

void LinkEditPresenter::save()
{
    if (m_link.isNull()) return;

    m_link->setName(this->viewProperty(PROPERTY(name)).toString());
    m_link->setParameter(dto::LinkDescription::Device,
                                this->viewProperty(PROPERTY(device)).toString());
    m_link->setParameter(dto::LinkDescription::BaudRate,
                                this->viewProperty(PROPERTY(baudRate)).toInt());
    m_link->setParameter(dto::LinkDescription::Port,
                                this->viewProperty(PROPERTY(port)).toInt());

    QStringList endpoints = this->viewProperty(PROPERTY(endpoints)).toStringList();
    endpoints = endpoints.toSet().toList(); // remove dublicates
    this->setViewProperty(PROPERTY(endpoints), endpoints);
    m_link->setParameter(dto::LinkDescription::Endpoints, endpoints.join(::separator));
    m_link->setParameter(dto::LinkDescription::UdpAutoResponse,
                                this->viewProperty(PROPERTY(autoResponse)).toBool());

    if (!m_service->save(m_link)) return;

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
