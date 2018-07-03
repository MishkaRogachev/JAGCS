#include "proxy_manager.h"

// Qt
#include <QNetworkProxy>

// Internal
#include "settings_provider.h"

using namespace domain;

ProxyManager::ProxyManager(QObject* parent):
    QObject(parent)
{}

ProxyManager::~ProxyManager()
{}

QNetworkProxy ProxyManager::proxy() const
{
    return QNetworkProxy::applicationProxy();
}

void ProxyManager::setProxy(const QNetworkProxy& proxy)
{
    if (QNetworkProxy::applicationProxy() == proxy) return;

    QNetworkProxy::setApplicationProxy(proxy);
    this->save();

    emit proxyChanged(proxy);
}

void ProxyManager::load()
{
    QNetworkProxy proxy;

    proxy.setType(static_cast<QNetworkProxy::ProxyType>(
                      settings::Provider::value(settings::proxy::type).toInt()));
    proxy.setHostName(settings::Provider::value(settings::proxy::hostName).toString());
    proxy.setPort(settings::Provider::value(settings::proxy::port).toInt());
    proxy.setUser(settings::Provider::value(settings::proxy::user).toString());
    proxy.setPassword(settings::Provider::value(settings::proxy::password).toString());

    this->setProxy(proxy);
}

void ProxyManager::save()
{
    QNetworkProxy proxy = this->proxy();

    settings::Provider::setValue(settings::proxy::type, proxy.type());
    settings::Provider::setValue(settings::proxy::hostName, proxy.hostName());
    settings::Provider::setValue(settings::proxy::port, proxy.port());
    settings::Provider::setValue(settings::proxy::user, proxy.user());
    settings::Provider::setValue(settings::proxy::password, proxy.password());
}
