#include "mavlink_udp_link.h"

// Qt
#include <QSerialPort>

using namespace data_source::mavlink;

UdpLink::UdpLink(const QString& portName, QObject* parent):
    AbstractLink(parent),
    m_port(new QSerialPort(portName, this))
{
    connect(m_port, &QSerialPort::readyRead, this, &UdpLink::onReadyRead);
}

void UdpLink::sendData(const QByteArray& data)
{
    m_port->write(data.data(), data.size());
}

void UdpLink::onReadyRead()
{

}
