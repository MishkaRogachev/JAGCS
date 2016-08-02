#include "network_settings_presenter.h"

// Qt
#include <QNetworkProxy>
#include <QDebug>

namespace
{
    const char* hostname = "hostname";
    const char* port = "port";
    const char* username = "username";
    const char* password = "password";
}

using namespace presentation;

NetworkSettingsPresenter::NetworkSettingsPresenter(QObject* parent):
    QObject(parent)
{}

void NetworkSettingsPresenter::restore()
{
    QNetworkProxy proxy = QNetworkProxy::applicationProxy();

    this->parent()->setProperty(::hostname, proxy.hostName());
    this->parent()->setProperty(::port, proxy.port());
    this->parent()->setProperty(::username, proxy.user());
    this->parent()->setProperty(::password, proxy.password());
}

void NetworkSettingsPresenter::apply()
{
    QNetworkProxy proxy;
    proxy.setType(QNetworkProxy::HttpProxy); // TODO: proxy type
    proxy.setHostName(this->parent()->property(::hostname).toString());
    proxy.setPort(this->parent()->property(::port).toInt());
    proxy.setUser(this->parent()->property(::username).toString());
    proxy.setPassword(this->parent()->property(::password).toString());
    QNetworkProxy::setApplicationProxy(proxy);
}
