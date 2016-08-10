#include "network_settings_presenter.h"

// Qt
#include <QNetworkProxy>
#include <QMap>
#include <QDebug>

#include "settings_provider.h"

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
    SettingsProvider* settings;
};

NetworkSettingsPresenter::NetworkSettingsPresenter(
        SettingsProvider* settings, QObject* view):
    BasePresenter(view),
    d(new Impl())
{
    d->settings = settings;

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
    d->settings->beginGroup(::networkProxyGroup);

    QString proxyType = d->typeModelMap.value(
                            static_cast<QNetworkProxy::ProxyType>(
                                d->settings->value(::proxyType).toInt()));
    this->invokeViewMethod(::setProxyType, proxyType);
    this->setViewProperty(::hostName, d->settings->value(::hostName));
    this->setViewProperty(::port, d->settings->value(::port));
    this->setViewProperty(::user, d->settings->value(::user));
    this->setViewProperty(::password, d->settings->value(::password));

    d->settings->endGroup();
}

void NetworkSettingsPresenter::apply()
{
    d->settings->beginGroup(::networkProxyGroup);

    d->settings->setValue(::proxyType, d->typeModelMap.key(
                          this->viewProperty(::proxyType).toString(),
                          QNetworkProxy::DefaultProxy));
    d->settings->setValue(::hostName, this->viewProperty(::hostName));
    d->settings->setValue(::port, this->viewProperty(::port));
    d->settings->setValue(::user, this->viewProperty(::user));
    d->settings->setValue(::password, this->viewProperty(::password));

    d->settings->endGroup();

    this->updateProxy();
}

void NetworkSettingsPresenter::updateProxy()
{
    d->settings->beginGroup(::networkProxyGroup);

    QNetworkProxy proxy;
    proxy.setType(static_cast<QNetworkProxy::ProxyType>(
                      d->settings->value(::proxyType).toInt()));
    proxy.setHostName(d->settings->value(::hostName).toString());
    proxy.setPort(d->settings->value(::port).toInt());
    proxy.setUser(d->settings->value(::user).toString());
    proxy.setPassword(d->settings->value(::password).toString());

    d->settings->endGroup();

    QNetworkProxy::setApplicationProxy(proxy);
}

