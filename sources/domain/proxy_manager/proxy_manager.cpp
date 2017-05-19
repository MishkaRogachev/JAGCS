#include "proxy_manager.h"

// Qt
#include <QNetworkProxy>

// Internal
#include "settings_provider.h"

using namespace domain;

ProxyManager::ProxyManager(QObject* parent):
    QObject(parent)
{
    this->load();
}

ProxyManager::~ProxyManager()
{
    this->save();
}

QNetworkProxy ProxyManager::proxy() const
{
    return QNetworkProxy::applicationProxy();
}

void ProxyManager::setProxy(const QNetworkProxy& proxy)
{
    if (QNetworkProxy::applicationProxy() == proxy) return;

    QNetworkProxy::setApplicationProxy(proxy);
    emit proxyChanged(proxy);
}

void ProxyManager::load()
{
    QNetworkProxy proxy;

    proxy.setType(static_cast<QNetworkProxy::ProxyType>(
                      SettingsProvider::value(settings::proxy::type).toInt()));
    proxy.setHostName(SettingsProvider::value(settings::proxy::hostName).toString());
    proxy.setPort(SettingsProvider::value(settings::proxy::port).toInt());
    proxy.setUser(SettingsProvider::value(settings::proxy::user).toString());
    proxy.setPassword(SettingsProvider::value(settings::proxy::password).toString());

    this->setProxy(proxy);
}

void ProxyManager::save()
{
    QNetworkProxy proxy = this->proxy();

    SettingsProvider::setValue(settings::proxy::type, proxy.type());
    SettingsProvider::setValue(settings::proxy::hostName, proxy.hostName());
    SettingsProvider::setValue(settings::proxy::port, proxy.port());
    SettingsProvider::setValue(settings::proxy::user, proxy.user());
    SettingsProvider::setValue(settings::proxy::password, proxy.password());
}
