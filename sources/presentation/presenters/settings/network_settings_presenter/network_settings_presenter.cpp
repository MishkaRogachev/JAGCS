#include "network_settings_presenter.h"

// Qt
#include <QNetworkProxy>
#include <QMap>
#include <QDebug>

namespace
{
    const char* proxyType = "proxyType";
    const char* hostname = "hostname";
    const char* port = "port";
    const char* username = "username";
    const char* password = "password";
}

using namespace presentation;

class NetworkSettingsPresenter::Impl
{
public:
    QMap<QNetworkProxy::ProxyType, QString> typeModelMap;
};

NetworkSettingsPresenter::NetworkSettingsPresenter(QObject* parent):
    QObject(parent),
    d(new Impl())
{
    d->typeModelMap.insert(QNetworkProxy::NoProxy, tr("No Proxy"));
    d->typeModelMap.insert(QNetworkProxy::DefaultProxy, tr("Default"));
    d->typeModelMap.insert(QNetworkProxy::Socks5Proxy, tr("SOCKS 5"));
    d->typeModelMap.insert(QNetworkProxy::HttpProxy, tr("HTTP"));
    d->typeModelMap.insert(QNetworkProxy::HttpCachingProxy, tr("Caching HTTP"));
    d->typeModelMap.insert(QNetworkProxy::FtpCachingProxy, tr("Caching FTP"));
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
    QNetworkProxy proxy = QNetworkProxy::applicationProxy();

    QMetaObject::invokeMethod(this->parent(), "setProxyType",
                              Q_ARG(QVariant, d->typeModelMap.value(proxy.type())));

    this->parent()->setProperty(::hostname, proxy.hostName());
    this->parent()->setProperty(::port, proxy.port());
    this->parent()->setProperty(::username, proxy.user());
    this->parent()->setProperty(::password, proxy.password());
}

void NetworkSettingsPresenter::apply()
{
    QNetworkProxy proxy;
    proxy.setType(d->typeModelMap.key(
                      this->parent()->property(::proxyType).toString(),
                      QNetworkProxy::DefaultProxy));
    proxy.setHostName(this->parent()->property(::hostname).toString());
    proxy.setPort(this->parent()->property(::port).toInt());
    proxy.setUser(this->parent()->property(::username).toString());
    proxy.setPassword(this->parent()->property(::password).toString());
    QNetworkProxy::setApplicationProxy(proxy);
}
