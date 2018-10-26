#include "communication_link.h"

// Qt
#include <QMetaEnum>
#include <QDebug>

namespace
{
    const QString paramSeparator = "|";
    const QString valueSeparator = "=";
}

using namespace domain;

namespace
{
    static QMap <LinkDescription::Type, QList<LinkDescription::Parameter> > typeParameters =
    {
        { LinkDescription::Serial,
          { LinkDescription::Device, LinkDescription::BaudRate } },
        { LinkDescription::Udp,
          { LinkDescription::Port, LinkDescription::Endpoints,
            LinkDescription::UdpAutoResponse } },
        { LinkDescription::Tcp,
          { LinkDescription::Address, LinkDescription::Port } },
        { LinkDescription::Bluetooth,
          { LinkDescription::Device, LinkDescription::Address } }
    };
}

QString LinkDescription::name() const
{
    return m_name;
}

void LinkDescription::setName(const QString& name)
{
    if (m_name == name) return;

    m_name = name;
    emit changed();
}

LinkDescription::Type LinkDescription::type() const
{
    return m_type;
}

void LinkDescription::setType(LinkDescription::Type type)
{
    if (m_type == type) return;

    m_type = type;
    emit changed();
}

QString LinkDescription::protocol() const
{
    return m_protocol;
}

void LinkDescription::setProtocol(const QString& protocol)
{
    if (m_protocol == protocol) return;

    m_protocol = protocol;
    emit changed();
}

QString LinkDescription::parameters() const
{
    QStringList list;
    int enumIndex = LinkDescription::staticMetaObject.indexOfEnumerator("Parameter");
    QMetaEnum enumerator = LinkDescription::staticMetaObject.enumerator(enumIndex);

    for (Parameter parameter: m_parameters.keys())
    {
        QString paramString = m_parameters.value(parameter).toString();

        list.append(QString(enumerator.valueToKey(parameter)) + ::valueSeparator +
                    paramString.remove(::paramSeparator).remove(::valueSeparator));
    }

    return list.join(::paramSeparator);
}

void LinkDescription::setParameters(const QString& arguments)
{
    int enumIndex = LinkDescription::staticMetaObject.indexOfEnumerator("Parameter");
    QMetaEnum enumerator = LinkDescription::staticMetaObject.enumerator(enumIndex);

    QMap<Parameter, QVariant> parameters;
    for (const QString& pairs: arguments.split(::paramSeparator))
    {
        QStringList pairList = pairs.split(::valueSeparator);
        if (pairList.count() < 2) continue;

        Parameter param = static_cast<Parameter>(enumerator.keyToValue(qPrintable(pairList.at(0))));
        if (param == UnknownParameter) continue;

        parameters[param] = pairList.at(1);
    }

    if (m_parameters == parameters) return;

    m_parameters = parameters;
    emit changed();
}

QVariant LinkDescription::parameter(Parameter key, const QVariant& parameter) const
{
    return m_parameters.value(key, parameter);
}

void LinkDescription::setParameter(Parameter key, const QVariant& parameter)
{
    if (!::typeParameters[m_type].contains(key) ||
        m_parameters.value(key) == parameter) return;

    m_parameters[key] = parameter;
    emit changed();
}

void LinkDescription::clearParameters()
{
    if (m_parameters.isEmpty()) return;

    m_parameters.clear();
    emit changed();
}

void LinkDescription::clearSuperfluousParameters()
{
    bool changed = false;

    for (Parameter parameter: m_parameters.keys())
    {
        if (::typeParameters[m_type].contains(parameter)) continue;

        m_parameters.remove(parameter);
        changed = true;
    }
    if (changed) emit LinkDescription::changed();
}

bool LinkDescription::isAutoConnect() const
{
    return m_autoConnect;
}

void LinkDescription::setAutoConnect(bool autoConnect)
{
    if (m_autoConnect == autoConnect) return;

    m_autoConnect = autoConnect;
    emit changed();
}

bool LinkDescription::isConnected() const
{
    return m_connected;
}

void LinkDescription::setConnected(bool connected)
{
    if (m_connected == connected) return;

    m_connected = connected;
    emit connectedChanged(connected);
}
