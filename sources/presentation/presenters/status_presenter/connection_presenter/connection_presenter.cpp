#include "connection_presenter.h"

// Internal
#include "connection_manager.h"
#include "settings_provider.h"
#include "settings.h"

using namespace presentation;

class ConnectionPresenter::Impl
{
public:
    domain::ConnectionManager* manager;
    domain::SettingsProvider* settings;
};

ConnectionPresenter::ConnectionPresenter(domain::ConnectionManager* manager,
                                         domain::SettingsProvider* settings,
                                         QObject* view):
    BasePresenter(view),
    d(new Impl())
{
    d->manager = manager;
    d->settings = settings;
}

ConnectionPresenter::~ConnectionPresenter()
{
    delete d;
}

QList<QObject*> ConnectionPresenter::links() const
{
    QList<QObject*> list;

    for (data_source::ILink* link: d->manager->links())
        list.append(link);

    return list;
}

void ConnectionPresenter::addSerialLink()
{
    d->settings->beginGroup(domain::connection_settings::group);

    d->manager->addNewSerialLink(
                d->settings->value(domain::connection_settings::serialDevice).toString(),
                d->settings->value(domain::connection_settings::baudRate).toInt());

    d->settings->endGroup();

    emit linksChanged(this->links());
}

void ConnectionPresenter::addUdpLink()
{
    d->settings->beginGroup(domain::connection_settings::group);

    d->manager->addNewUdpLink(
                d->settings->value(domain::connection_settings::hostPort).toInt(),
                QHostAddress(d->settings->value(domain::connection_settings::address).toString()),
                d->settings->value(domain::connection_settings::port).toInt());

    d->settings->endGroup();

    emit linksChanged(this->links());
}
