#include "network_settings_presenter.h"

// Qt
#include <QNetworkProxy>
#include <QMap>
#include <QDebug>

// Internal
#include "settings_provider.h"
#include "settings.h"

using namespace presentation;
using namespace domain;

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

void NetworkSettingsPresenter::connectView(QObject* view)
{
    connect(view, SIGNAL(apply()), this, SLOT(onApply()));
    connect(view, SIGNAL(restore()), this, SLOT(onRestore()));

    QStringList typeModel = d->typeModelMap.values();
    this->setViewProperty(PROPERTY(typeModel), typeModel);

    this->onRestore();
}

void NetworkSettingsPresenter::onApply()
{
    SettingsProvider::beginGroup(proxy_settings::group);

    SettingsProvider::setValue(proxy_settings::type, d->typeModelMap.key(
                               this->viewProperty(proxy_settings::type).toString()));
    SettingsProvider::setValue(proxy_settings::hostName,
                               this->viewProperty(proxy_settings::hostName));
    SettingsProvider::setValue(proxy_settings::port,
                               this->viewProperty(proxy_settings::port));
    SettingsProvider::setValue(proxy_settings::user,
                               this->viewProperty(proxy_settings::user));
    SettingsProvider::setValue(proxy_settings::password,
                               this->viewProperty(proxy_settings::password));

    SettingsProvider::endGroup();

    this->updateProxy();
}

void NetworkSettingsPresenter::onRestore()
{
    SettingsProvider::beginGroup(proxy_settings::group);

    QString type = d->typeModelMap.value(static_cast<QNetworkProxy::ProxyType>(
                        SettingsProvider::value(proxy_settings::type).toInt()));
    this->invokeViewMethod("setProxyType", type);
    this->setViewProperty(proxy_settings::hostName,
                          SettingsProvider::value(proxy_settings::hostName));
    this->setViewProperty(proxy_settings::port,
                          SettingsProvider::value(proxy_settings::port));
    this->setViewProperty(proxy_settings::user,
                          SettingsProvider::value(proxy_settings::user));
    this->setViewProperty(proxy_settings::password,
                          SettingsProvider::value(proxy_settings::password));

    SettingsProvider::endGroup();
}

void NetworkSettingsPresenter::updateProxy()
{
    SettingsProvider::beginGroup(proxy_settings::group);

    QNetworkProxy proxy;
    proxy.setType(static_cast<QNetworkProxy::ProxyType>(
                      SettingsProvider::value(proxy_settings::type).toInt()));
    proxy.setHostName(SettingsProvider::value(proxy_settings::hostName).toString());
    proxy.setPort(SettingsProvider::value(proxy_settings::port).toInt());
    proxy.setUser(SettingsProvider::value(proxy_settings::user).toString());
    proxy.setPassword(SettingsProvider::value(proxy_settings::password).toString());

    SettingsProvider::endGroup();

    QNetworkProxy::setApplicationProxy(proxy);
}

