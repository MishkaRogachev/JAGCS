#include "presenters_factory.h"

// Internal
#include "domain_entry.h"

#include "video_presenter.h"
#include "map_presenter.h"
#include "flight_presenter.h"
#include "status_presenter.h"
#include "settings_presenter.h"

using namespace presentation;

PresentersFactory::PresentersFactory(domain::DomainEntry* entry, QObject* parent):
    QObject(parent),
    m_entry(entry)
{}

QObject* PresentersFactory::createVideoPresenter(QObject* parent)
{
    auto presenter = new VideoPresenter(parent);
    presenter->setView(parent);
    return presenter;
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
    auto presenter = new FlightPresenter(m_entry->vehicleService(), parent);
    presenter->setView(parent);
    return presenter;
}

QObject* PresentersFactory::createSettingsPresenter(QObject* parent)
{
     auto presenter = new SettingsPresenter(m_entry, parent);
     presenter->setView(parent);
     return presenter;
}
