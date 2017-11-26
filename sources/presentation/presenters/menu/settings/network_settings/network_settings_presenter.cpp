#include "network_settings_presenter.h"

// Qt
#include <QNetworkProxy>
#include <QMap>
#include <QDebug>

// Internal
#include "proxy_manager.h"

using namespace presentation;
using namespace domain;

class NetworkSettingsPresenter::Impl
{
public:
    domain::ProxyManager manager;
    QMap<QNetworkProxy::ProxyType, QString> typeModelMap;
};

NetworkSettingsPresenter::NetworkSettingsPresenter(QObject* parent):
    BasePresenter(parent),
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
{}

void NetworkSettingsPresenter::updateView()
{
    QNetworkProxy proxy = d->manager.proxy();

    QStringList typeModel = d->typeModelMap.values();
    this->setViewProperty(PROPERTY(typeModel), typeModel);

    QString type = d->typeModelMap.value(proxy.type());
    this->invokeViewMethod(PROPERTY(setProxyType), type);
    this->setViewProperty(PROPERTY(hostName), proxy.hostName());
    this->setViewProperty(PROPERTY(port), proxy.port());
    this->setViewProperty(PROPERTY(user), proxy.user());
    this->setViewProperty(PROPERTY(password), proxy.password());

    this->setViewProperty(PROPERTY(changed), false);
}

void NetworkSettingsPresenter::save()
{
    QNetworkProxy proxy;

    proxy.setType(d->typeModelMap.key(this->viewProperty(PROPERTY(type)).toString()));
    proxy.setHostName(this->viewProperty(PROPERTY(hostName)).toString());
    proxy.setPort(this->viewProperty(PROPERTY(port)).toInt());
    proxy.setUser(this->viewProperty(PROPERTY(user)).toString());
    proxy.setPassword(this->viewProperty(PROPERTY(password)).toString());

    d->manager.setProxy(proxy);

    this->setViewProperty(PROPERTY(changed), false);
}


