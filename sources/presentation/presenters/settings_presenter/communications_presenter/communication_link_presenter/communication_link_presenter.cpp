#include "communication_link_presenter.h"

// Qt
#include <QMap>
#include <QVariant>
#include <QSerialPortInfo>
#include <QDebug>

// Internal
#include "link_description.h"

namespace
{
    static const QMap <data_source::LinkDescription::Type, QString> typeMap =
    {
        { data_source::LinkDescription::Udp, QObject::tr("UDP") },
        { data_source::LinkDescription::Serial, QObject::tr("Serial") }
    };
}

using namespace presentation;

CommunicationLinkPresenter::CommunicationLinkPresenter(
        const data_source::LinkDescriptionPtr& description,
        QObject* parent):
    BasePresenter(parent),
    m_description(description)
{}

data_source::LinkDescriptionPtr CommunicationLinkPresenter::description() const
{
    return m_description;
}

void CommunicationLinkPresenter::updateView()
{
    this->setViewSignalsEnbled(false);

    this->setViewProperty(PROPERTY(type), m_description->type());
    this->setViewProperty(PROPERTY(typeName), ::typeMap.value(m_description->type()));
    this->setViewProperty(PROPERTY(name), m_description->name());
    this->setViewProperty(PROPERTY(port), m_description->port());
    this->setViewProperty(PROPERTY(device), m_description->device());
    this->setViewProperty(PROPERTY(baudRate), m_description->baudRate());
    this->setViewProperty(PROPERTY(autoConnect), m_description->isAutoConnect());

    this->setViewSignalsEnbled(true);
}

void CommunicationLinkPresenter::connectView(QObject* view)
{
    QStringList typeNames = ::typeMap.values();
    this->setViewProperty(PROPERTY(typeNames), typeNames);

    QStringList devices;
    for (const QSerialPortInfo& info: QSerialPortInfo::availablePorts())
        devices.append(info.portName());
    this->setViewProperty(PROPERTY(devices), devices);

    QVariantList baudRates;
    for (qint32 rate: QSerialPortInfo::standardBaudRates())
        baudRates.append(rate);
    this->setViewProperty(PROPERTY(baudRates), baudRates);

    this->updateView();
}

void CommunicationLinkPresenter::setViewSignalsEnbled(bool enabled)
{
    if (enabled)
    {
        connect(m_view, SIGNAL(setType(QString)), this, SLOT(onSetType(QString)));
        connect(m_view, SIGNAL(setName(QString)), this, SLOT(onSetName(QString)));
        connect(m_view, SIGNAL(setPort(int)), this, SLOT(onSetPort(int)));
        connect(m_view, SIGNAL(setDevice(QString)), this, SLOT(onSetDevice(QString)));
        connect(m_view, SIGNAL(setBaudRate(int)), this, SLOT(onSetBaudRate(int)));
        connect(m_view, SIGNAL(remove()), this, SIGNAL(remove()));
    }
    else
    {
        disconnect(m_view, 0, this, 0);
    }
}

void CommunicationLinkPresenter::onSetType(const QString& type)
{
    m_description->setType(::typeMap.key(
                              type, data_source::LinkDescription::UnknownType));
}

void CommunicationLinkPresenter::onSetName(const QString& name)
{
    m_description->setName(name);
}

void CommunicationLinkPresenter::onSetPort(int port)
{
    m_description->setPort(port);
}

void CommunicationLinkPresenter::onSetDevice(const QString& device)
{
    m_description->setDevice(device);
}

void CommunicationLinkPresenter::onSetBaudRate(int rate)
{
    m_description->setBaudRate(rate);
}
