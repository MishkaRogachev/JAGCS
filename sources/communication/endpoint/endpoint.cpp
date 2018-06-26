#include "endpoint.h"

using namespace comm;

Endpoint::Endpoint(const QHostAddress& address, quint16 port):
    m_address(address),
    m_port(port)
{}

QHostAddress Endpoint::address() const
{
    return m_address;
}

void Endpoint::setAddress(const QHostAddress& address)
{
    m_address = address;
}

quint16 Endpoint::port() const
{
    return m_port;
}

void Endpoint::setPort(quint16 port)
{
    m_port = port;
}

bool Endpoint::isValid() const
{
    return !m_address.isNull() && m_port > 0;
}

bool Endpoint::operator ==(const Endpoint& other)
{
    return m_address == other.address() && m_port == other.port();
}
