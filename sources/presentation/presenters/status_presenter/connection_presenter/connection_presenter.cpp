#include "connection_presenter.h"

// Internal
#include "connection_manager.h"
#include "settings_provider.h"

namespace
{
    const char* connectionGroup = "Connection";
    const char* serialDevice = "serialDevice";
    const char* baudRate = "baudRate";
    const char* hostPort = "hostPort";
    const char* address = "address";
    const char* port = "port";
}

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

void ConnectionPresenter::addSerialLink()
{
    d->settings->beginGroup(::connectionGroup);

    d->manager->addNewSerialLink(d->settings->value(::serialDevice).toString(),
                                 d->settings->value(::baudRate).toInt());

    d->settings->endGroup();
}

void ConnectionPresenter::addUdpLink()
{
    d->settings->beginGroup(::connectionGroup);

    d->manager->addNewUdpLink(d->settings->value(::hostPort).toInt(),
                              QHostAddress(d->settings->value(::address).toString()),
                              d->settings->value(::port).toInt());

    d->settings->endGroup();
}
