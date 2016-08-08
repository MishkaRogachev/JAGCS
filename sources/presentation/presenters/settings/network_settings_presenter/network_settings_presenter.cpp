#include "network_settings_presenter.h"

// Qt
#include <QNetworkProxy>
#include <QSettings>
#include <QMap>
#include <QDebug>

namespace
{
    const char* networkProxyGroup = "NetworkProxy";
    const char* setProxyType = "setProxyType";
    const char* proxyType = "proxyType";
    const char* hostName = "hostName";
    const char* port = "port";
    const char* user = "user";
    const char* password = "password";
}

using namespace presentation;

class NetworkSettingsPresenter::Impl
{
public:
    QMap<QNetworkProxy::ProxyType, QString> typeModelMap;
};

NetworkSettingsPresenter::NetworkSettingsPresenter(QObject* view):
    BasePresenter(view),
    d(new Impl())
{
    d->typeModelMap.insert(QNetworkProxy::NoProxy, tr("No Proxy"));
    d->typeModelMap.insert(QNetworkProxy::DefaultProxy, tr("Default"));
    d->typeModelMap.insert(QNetworkProxy::Socks5Proxy, tr("SOCKS 5"));
    d->typeModelMap.insert(QNetworkProxy::HttpProxy, tr("HTTP"));
    d->typeModelMap.insert(QNetworkProxy::HttpCachingProxy, tr("Caching HTTP"));
    d->typeModelMap.insert(QNetworkProxy::FtpCachingProxy, tr("Caching FTP"));

    this->updateProxy();
}

NetworkSettingsPresenter::~NetworkSettingsPresenter()
{
    delete d;
}

QStringList NetworkSettingsPresenter::typeModel() const
{
    return d->typeModelMap.values();
}

void NetworkSettingsPresenter::restore()
{
    QSettings settings;
    settings.beginGroup(::networkProxyGroup);

    QString proxyType = d->typeModelMap.value(
                            static_cast<QNetworkProxy::ProxyType>(
                                settings.value(::proxyType).toInt()));
    this->invokeViewMethod(::setProxyType, proxyType);
    this->setViewProperty(::hostName, settings.value(::hostName));
    this->setViewProperty(::port, settings.value(::port));
    this->setViewProperty(::user, settings.value(::user));
    this->setViewProperty(::password, settings.value(::password));
}

void NetworkSettingsPresenter::apply()
{
    QSettings settings;
    settings.beginGroup(::networkProxyGroup);

    settings.setValue(::proxyType, d->typeModelMap.key(
                          this->viewProperty(::proxyType).toString(),
                          QNetworkProxy::DefaultProxy));
    settings.setValue(::hostName, this->viewProperty(::hostName));
    settings.setValue(::port, this->viewProperty(::port));
    settings.setValue(::user, this->viewProperty(::user));
    settings.setValue(::password, this->viewProperty(::password));

    settings.sync();

    this->updateProxy();
}

void NetworkSettingsPresenter::updateProxy()
{
    QSettings settings;
    settings.beginGroup(::networkProxyGroup);

    QNetworkProxy proxy;
    proxy.setType(static_cast<QNetworkProxy::ProxyType>(
                      settings.value(::proxyType).toInt()));
    proxy.setHostName(settings.value(::hostName).toString());
    proxy.setPort(settings.value(::port).toInt());
    proxy.setUser(settings.value(::user).toString());
    proxy.setPassword(settings.value(::password).toString());

    QNetworkProxy::setApplicationProxy(proxy);
}

