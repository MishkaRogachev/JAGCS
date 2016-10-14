#include "presenters_factory.h"

// Internal
#include "domain_entry.h"

#include "video_presenter.h"
#include "map_presenter.h"

#include "flight_presenter.h"

#include "status_presenter.h"

#include "video_settings_presenter.h"
#include "connection_settings_presenter.h"
#include "network_settings_presenter.h"

using namespace presentation;

PresentersFactory::PresentersFactory(domain::DomainEntry* entry, QObject* parent):
    QObject(parent),
    m_entry(entry)
{}

QObject* PresentersFactory::createVideoPresenter(QObject* parent)
{
    return new VideoPresenter(parent);
}

QObject* PresentersFactory::createMapPresenter(QObject* parent)
{
    return new MapPresenter(parent);
}

QObject* PresentersFactory::createStatusPresenter(QObject* parent)
{
    return new StatusPresenter(parent);
}

QObject* PresentersFactory::createFlightPresenter(QObject* parent)
{
    return new FlightPresenter(m_entry->vehicleService(), parent);
}

QObject* PresentersFactory::createConnectionSettingsPresenter(QObject* parent)
{
     return new ConnectionSettingsPresenter(m_entry->communicator(),
                                            parent);
}

QObject* PresentersFactory::createVideoSettingsPresenter(QObject* parent)
{
    return new VideoSettingsPresenter(parent);
}

QObject* PresentersFactory::createNetworkSettingsPresenter(QObject* parent)
{
    return new NetworkSettingsPresenter(parent);
}
