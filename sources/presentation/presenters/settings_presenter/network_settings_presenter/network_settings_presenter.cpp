#include "network_settings_presenter.h"

// Qt
#include <QNetworkProxy>
#include <QMap>
#include <QDebug>

// Internal
#include "settings_provider.h"
#include "settings.h"

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
    domain::SettingsProvider::beginGroup(domain::proxy_settings::group);

    QString type = d->typeModelMap.value(static_cast<QNetworkProxy::ProxyType>(
                     domain::SettingsProvider::value(domain::proxy_settings::type).toInt()));
    this->invokeViewMethod("setProxyType", type);
    this->setViewProperty(domain::proxy_settings::hostName,
                          domain::SettingsProvider::value(domain::proxy_settings::hostName));
    this->setViewProperty(domain::proxy_settings::port,
                          domain::SettingsProvider::value(domain::proxy_settings::port));
    this->setViewProperty(domain::proxy_settings::user,
                          domain::SettingsProvider::value(domain::proxy_settings::user));
    this->setViewProperty(domain::proxy_settings::password,
                          domain::SettingsProvider::value(domain::proxy_settings::password));

    domain::SettingsProvider::endGroup();
}

void NetworkSettingsPresenter::apply()
{
    domain::SettingsProvider::beginGroup(domain::proxy_settings::group);

    domain::SettingsProvider::setValue(domain::proxy_settings::type, d->typeModelMap.key(
                  this->viewProperty(domain::proxy_settings::type).toString()));
    domain::SettingsProvider::setValue(domain::proxy_settings::hostName,
                          this->viewProperty(domain::proxy_settings::hostName));
    domain::SettingsProvider::setValue(domain::proxy_settings::port,
                          this->viewProperty(domain::proxy_settings::port));
    domain::SettingsProvider::setValue(domain::proxy_settings::user,
                          this->viewProperty(domain::proxy_settings::user));
    domain::SettingsProvider::setValue(domain::proxy_settings::password,
                          this->viewProperty(domain::proxy_settings::password));

    domain::SettingsProvider::endGroup();

    this->updateProxy();
}

void NetworkSettingsPresenter::updateProxy()
{
    domain::SettingsProvider::beginGroup(domain::proxy_settings::group);

    QNetworkProxy proxy;
    proxy.setType(static_cast<QNetworkProxy::ProxyType>(
                      domain::SettingsProvider::value(domain::proxy_settings::type).toInt()));
    proxy.setHostName(domain::SettingsProvider::value(domain::proxy_settings::hostName).toString());
    proxy.setPort(domain::SettingsProvider::value(domain::proxy_settings::port).toInt());
    proxy.setUser(domain::SettingsProvider::value(domain::proxy_settings::user).toString());
    proxy.setPassword(domain::SettingsProvider::value(domain::proxy_settings::password).toString());

    domain::SettingsProvider::endGroup();

    QNetworkProxy::setApplicationProxy(proxy);
}

