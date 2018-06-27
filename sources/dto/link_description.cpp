#include "link_description.h"

// Qt
#include <QMetaEnum>
#include <QDebug>

namespace
{
    const QString paramSeparator = "\\;";
    const QString valueSeparator = "\\:";
}

using namespace dto;

namespace
{
    static QMap <LinkDescription::Type, QList<LinkDescription::Parameter> > typeParameters =
    {
        { LinkDescription::Serial, { LinkDescription::Device, LinkDescription::BaudRate } },
        { LinkDescription::Udp, { LinkDescription::Port, LinkDescription::Endpoints,
                                  LinkDescription::UdpAutoResponse } },
        { LinkDescription::Tcp, { LinkDescription::Address, LinkDescription::Port } },
        { LinkDescription::Bluetooth, { LinkDescription::Device, LinkDescription::Address } }
    };
}

QString LinkDescription::name() const
{
    return m_name;
}

void LinkDescription::setName(const QString& name)
{
    m_name = name;
}

LinkDescription::Type LinkDescription::type() const
{
    return m_type;
}

void LinkDescription::setType(LinkDescription::Type type)
{
    m_type = type;
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

    m_parameters.clear();
    for (const QString& pairs: arguments.split(::paramSeparator))
    {
        QStringList pairList = pairs.split(::valueSeparator);
        if (pairList.count() < 2) continue;

        Parameter param = static_cast<Parameter>(enumerator.keyToValue(qPrintable(pairList.at(0))));
        if (param == UnknownParameter) continue;

        m_parameters[param] = pairList.at(1);
    }
}

QVariant LinkDescription::parameter(Parameter key, const QVariant& parameter)
{
    return m_parameters.value(key, parameter);
}

void LinkDescription::setParameter(Parameter key, const QVariant& parameter)
{
    if (::typeParameters[m_type].contains(key)) m_parameters[key] = parameter;
}

void LinkDescription::clearParameters()
{
    m_parameters.clear();
}

void LinkDescription::clearSuperfluousParameters()
{
    for (Parameter parameter: m_parameters.keys())
    {
        if (::typeParameters[m_type].contains(parameter)) continue;

        m_parameters.remove(parameter);
    }
}

bool LinkDescription::isAutoConnect() const
{
    return m_autoConnect;
}

void LinkDescription::setAutoConnect(bool autoConnect)
{
    m_autoConnect = autoConnect;
}

bool LinkDescription::isConnected() const
{
    return m_connected;
}

void LinkDescription::setConnected(bool connected)
{
    m_connected = connected;
}

LinkDescription::Protocol LinkDescription::protocol() const
{
    return m_protocol;
}

void LinkDescription::setProtocol(Protocol protocol)
{
    m_protocol = protocol;
}
