#include "communication_link_presenter.h"

// Qt
#include <QMap>
#include <QVariant>
#include <QSerialPortInfo>
#include <QDebug>

// Internal
#include "settings_provider.h"

#include "db_facade.h"
#include "link_description.h"\

#include "communication_service.h"

using namespace presentation;

CommunicationLinkPresenter::CommunicationLinkPresenter(
        db::DbFacade* dbFacade,
        domain::CommunicationService* service,
        const db::LinkDescriptionPtr& description,
        QObject* parent):
    BasePresenter(parent),
    m_dbFacade(dbFacade),
    m_service(service),
    m_description(description)
{}

db::LinkDescriptionPtr CommunicationLinkPresenter::description() const
{
    return m_description;
}

void CommunicationLinkPresenter::updateView()
{
    this->setViewSignalsEnbled(false);

    this->setViewProperty(PROPERTY(type), m_description->type());
    this->setViewProperty(PROPERTY(name), m_description->name());
    this->setViewProperty(PROPERTY(port), m_description->port());
    this->setViewProperty(PROPERTY(device), m_description->device());
    this->setViewProperty(PROPERTY(baudRate), m_description->baudRate());

    this->setViewSignalsEnbled(true);
}

void CommunicationLinkPresenter::updateStatistics()
{
    this->setViewProperty(PROPERTY(connected), m_description->isConnected());
    this->invokeViewMethod(PROPERTY(updateStatistics),
                           m_description->bytesSentSec(),
                           m_description->bytesRecvSec());
}

void CommunicationLinkPresenter::connectView(QObject* view)
{
    QStringList devices;
    devices.append(QString());
    for (const QSerialPortInfo& info: QSerialPortInfo::availablePorts())
        devices.append(info.portName());
    this->setViewProperty(PROPERTY(devices), devices);

    QVariantList baudRates;
    for (qint32 rate: QSerialPortInfo::standardBaudRates())
        baudRates.append(rate);
    this->setViewProperty(PROPERTY(baudRates), baudRates);

    this->setViewProperty(PROPERTY(statisticsCount),
                          domain::SettingsProvider::value(
                              settings::communication::statisticsCount));

    this->updateView();
}

void CommunicationLinkPresenter::setViewSignalsEnbled(bool enabled)
{
    if (enabled)
    {
        connect(m_view, SIGNAL(setName(QString)), this, SLOT(onSetName(QString)));
        connect(m_view, SIGNAL(setPort(int)), this, SLOT(onSetPort(int)));
        connect(m_view, SIGNAL(setDevice(QString)), this, SLOT(onSetDevice(QString)));
        connect(m_view, SIGNAL(setBaudRate(int)), this, SLOT(onSetBaudRate(int)));
        connect(m_view, SIGNAL(setConnected(bool)), this, SLOT(onSetConnected(bool)));
        connect(m_view, SIGNAL(remove()), this, SLOT(onRemove()));
    }
    else
    {
        disconnect(m_view, 0, this, 0);
    }
}

void CommunicationLinkPresenter::onSetName(const QString& name)
{
    if (m_description->name() == name) return;

    m_description->setName(name);
    m_dbFacade->save(m_description);
}

void CommunicationLinkPresenter::onSetPort(int port)
{
    if (m_description->port() == port) return;

    m_description->setPort(port);
    m_dbFacade->save(m_description);
}

void CommunicationLinkPresenter::onSetDevice(const QString& device)
{
    if (m_description->device() == device) return;

    m_description->setDevice(device);
    m_dbFacade->save(m_description);
}

void CommunicationLinkPresenter::onSetBaudRate(int rate)
{
    if (m_description->baudRate() == rate) return;

    m_description->setBaudRate(rate);
    m_dbFacade->save(m_description);
}

void CommunicationLinkPresenter::onSetConnected(bool connected)
{
    m_service->setLinkConnected(m_description, connected);
}

void CommunicationLinkPresenter::onRemove()
{
    m_dbFacade->remove(m_description);
}
