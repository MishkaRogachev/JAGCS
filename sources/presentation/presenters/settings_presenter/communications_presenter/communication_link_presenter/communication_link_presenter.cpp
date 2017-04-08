#include "communication_link_presenter.h"

// Qt
#include <QMap>
#include <QVariant>
#include <QSerialPortInfo>

// Internal
#include "link_description.h"

namespace
{
    static const QMap <data_source::LinkDescription::Type, QString> typeMap =
    {
        { data_source::LinkDescription::Udp, QObject::tr("Udp") },
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
    this->setViewProperty(PROPERTY(type), m_description->type());
    this->setViewProperty(PROPERTY(typeName), ::typeMap.value(m_description->type()));
    this->setViewProperty(PROPERTY(name), m_description->name());
    this->setViewProperty(PROPERTY(port), m_description->port());
    this->setViewProperty(PROPERTY(device), m_description->device());
    this->setViewProperty(PROPERTY(baudRate), m_description->baudRate());
    this->setViewProperty(PROPERTY(autoConnect), m_description->isAutoConnect());
}

void CommunicationLinkPresenter::connectView(QObject* view)
{
    connect(view, SIGNAL(setType(QString)), this, SLOT(onSetType(QString)));
    connect(view, SIGNAL(setName(QString)), this, SLOT(onSetName(QString)));
    connect(view, SIGNAL(setPort(int)), this, SLOT(onSetPort(int)));
    connect(view, SIGNAL(setDevice(QString)), this, SLOT(onSetDevice(QString)));
    connect(view, SIGNAL(setBaudRate(int)), this, SLOT(onSetBaudRate(int)));
    connect(view, SIGNAL(remove()), this, SLOT(remove()));

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
