#include "communication_link_presenter.h"

// Qt
#include <QMap>
#include <QVariant>

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
        data_source::LinkDescription* description,
        QObject* parent):
    BasePresenter(parent),
    m_description(description)
{}

data_source::LinkDescription* CommunicationLinkPresenter::description() const
{
    return m_description;
}

void CommunicationLinkPresenter::updateView()
{
    this->setViewProperty(PROPERTY(name), m_description->name());
    this->setViewProperty(PROPERTY(port), m_description->port());
    this->setViewProperty(PROPERTY(autoConnect), m_description->isAutoConnect());
   /* TODO:
    * property int type: LinkDescription.UnknownType
    property bool connected: false

    property alias name: nameField.text
    property alias typeName: typeBox.currentText
    property alias typeNames: typeBox.model
    property alias port: portBox.value
    property alias device: deviceBox.currentText
    property alias devices: deviceBox.model
    property alias baudRate: baudBox.currentText
    property alias baudRates: baudBox.model
    property alias autoConnect: autoconnectBox.checked*/
}

void CommunicationLinkPresenter::connectView(QObject* view)
{
    connect(view, SIGNAL(save()), this, SLOT(onSave()));
    connect(view, SIGNAL(restore()), this, SLOT(onRestore()));
    connect(view, SIGNAL(remove()), this, SLOT(remove()));

    QStringList typeNames = ::typeMap.values();
    this->setViewProperty(PROPERTY(typeNames), typeNames);
    this->updateView();
}

void CommunicationLinkPresenter::onSave()
{
    m_description->setName(this->viewProperty(PROPERTY(name)).toString());
    m_description->setPort(this->viewProperty(PROPERTY(port)).toInt());
}

void CommunicationLinkPresenter::onRestore()
{
    this->updateView();
}
