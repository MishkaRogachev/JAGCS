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

quint16 Endpoint::port() const
{
    return m_port;
}

QHostAddress& Endpoint::rAddress()
{
    return m_address;
}

quint16& Endpoint::rPort()
{
    return m_port;
}

bool Endpoint::operator ==(const Endpoint& other)
{
    return m_address == other.address() && m_port == other.port();
}
