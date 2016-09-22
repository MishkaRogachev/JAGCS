#include "connection_settings_presenter.h"

// Internal
#include "connection_manager.h"
#include "settings_provider.h"
#include "settings.h"

// Qt
#include <QSerialPortInfo>
#include <QDebug>

using namespace presentation;

class ConnectionSettingsPresenter::Impl
{
public:
    domain::ConnectionManager* manager;
    domain::SettingsProvider* settings;
};

ConnectionSettingsPresenter::ConnectionSettingsPresenter(
        domain::ConnectionManager* manager,
        domain::SettingsProvider* settings,
        QObject* view):
    BasePresenter(view),
    d(new Impl())
{
    d->manager = manager;
    d->settings = settings;
}

ConnectionSettingsPresenter::~ConnectionSettingsPresenter()
{
    delete d;
}

QList<QObject*> ConnectionSettingsPresenter::links() const
{
    QList<QObject*> list;

    for (data_source::ILink* link: d->manager->links())
        list.append(link);

    return list;
}

QStringList ConnectionSettingsPresenter::serialDevices() const
{
    QStringList devices;

    for (const QSerialPortInfo& info: QSerialPortInfo::availablePorts())
        devices.append(info.portName());

    return devices;
}

QVariantList ConnectionSettingsPresenter::serialBaudRates() const
{
    QVariantList rates;
    for (qint32 rate: QSerialPortInfo::standardBaudRates())
        rates.append(rate);

    return rates;
}

void ConnectionSettingsPresenter::addSerialLink()
{
    d->settings->beginGroup(domain::connection_settings::group);

    d->manager->addNewSerialLink(
                d->settings->value(domain::connection_settings::serialDevice).toString(),
                d->settings->value(domain::connection_settings::baudRate).toInt());

    d->settings->endGroup();

    emit linksChanged(this->links());
}

void ConnectionSettingsPresenter::addUdpLink()
{
    d->settings->beginGroup(domain::connection_settings::group);

    d->manager->addNewUdpLink(
                d->settings->value(domain::connection_settings::hostPort).toInt(),
                d->settings->value(domain::connection_settings::address).toString(),
                d->settings->value(domain::connection_settings::port).toInt());

    d->settings->endGroup();

    emit linksChanged(this->links());
}

void ConnectionSettingsPresenter::removeLink(QObject* link)
{
    d->manager->removeLink(qobject_cast<data_source::ILink*>(link));

    emit linksChanged(this->links());
}
