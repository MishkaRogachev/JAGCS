#include "proxy_manager.h"

// Qt
#include <QNetworkProxy>

// Internal
#include "settings.h"
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
                      SettingsProvider::value(proxy_settings::type).toInt()));
    proxy.setHostName(SettingsProvider::value(proxy_settings::hostName).toString());
    proxy.setPort(SettingsProvider::value(proxy_settings::port).toInt());
    proxy.setUser(SettingsProvider::value(proxy_settings::user).toString());
    proxy.setPassword(SettingsProvider::value(proxy_settings::password).toString());

    this->setProxy(proxy);
}

void ProxyManager::save()
{
    QNetworkProxy proxy = this->proxy();

    SettingsProvider::setValue(proxy_settings::type, proxy.type());
    SettingsProvider::setValue(proxy_settings::hostName, proxy.hostName());
    SettingsProvider::setValue(proxy_settings::port, proxy.port());
    SettingsProvider::setValue(proxy_settings::user, proxy.user());
    SettingsProvider::setValue(proxy_settings::password, proxy.password());
}
