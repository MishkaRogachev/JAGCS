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
    domain::SettingsProvider* settings;
};

NetworkSettingsPresenter::NetworkSettingsPresenter(
        domain::SettingsProvider* settings, QObject* view):
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
    d->settings->beginGroup(domain::proxy_settings::group);

    QString type = d->typeModelMap.value(static_cast<QNetworkProxy::ProxyType>(
                     d->settings->value(domain::proxy_settings::type).toInt()));
    this->invokeViewMethod("setProxyType", type);
    this->setViewProperty(domain::proxy_settings::hostName,
                          d->settings->value(domain::proxy_settings::hostName));
    this->setViewProperty(domain::proxy_settings::port,
                          d->settings->value(domain::proxy_settings::port));
    this->setViewProperty(domain::proxy_settings::user,
                          d->settings->value(domain::proxy_settings::user));
    this->setViewProperty(domain::proxy_settings::password,
                          d->settings->value(domain::proxy_settings::password));

    d->settings->endGroup();
}

void NetworkSettingsPresenter::apply()
{
    d->settings->beginGroup(domain::proxy_settings::group);

    d->settings->setValue(domain::proxy_settings::type, d->typeModelMap.key(
                  this->viewProperty(domain::proxy_settings::type).toString()));
    d->settings->setValue(domain::proxy_settings::hostName,
                          this->viewProperty(domain::proxy_settings::hostName));
    d->settings->setValue(domain::proxy_settings::port,
                          this->viewProperty(domain::proxy_settings::port));
    d->settings->setValue(domain::proxy_settings::user,
                          this->viewProperty(domain::proxy_settings::user));
    d->settings->setValue(domain::proxy_settings::password,
                          this->viewProperty(domain::proxy_settings::password));

    d->settings->endGroup();

    this->updateProxy();
}

void NetworkSettingsPresenter::updateProxy()
{
    d->settings->beginGroup(domain::proxy_settings::group);

    QNetworkProxy proxy;
    proxy.setType(static_cast<QNetworkProxy::ProxyType>(
                      d->settings->value(domain::proxy_settings::type).toInt()));
    proxy.setHostName(d->settings->value(domain::proxy_settings::hostName).toString());
    proxy.setPort(d->settings->value(domain::proxy_settings::port).toInt());
    proxy.setUser(d->settings->value(domain::proxy_settings::user).toString());
    proxy.setPassword(d->settings->value(domain::proxy_settings::password).toString());

    d->settings->endGroup();

    QNetworkProxy::setApplicationProxy(proxy);
}

