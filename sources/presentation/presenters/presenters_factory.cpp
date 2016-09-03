#include "presenters_factory.h"

// Internal
#include "domain_entry.h"

#include "video_presenter.h"
#include "map_presenter.h"

#include "status_presenter.h"
#include "connection_presenter.h"

#include "video_settings_presenter.h"
#include "network_settings_presenter.h"

using namespace presentation;

PresentersFactory::PresentersFactory(domain::DomainEntry* entry, QObject* parent):
    QObject(parent),
    m_entry(entry)
{}

QObject* PresentersFactory::createVideoPresenter(QObject* parent)
{
    return new VideoPresenter(m_entry->settings, parent);
}

QObject* PresentersFactory::createMapPresenter(QObject* parent)
{
    return new MapPresenter(parent);
}

QObject* PresentersFactory::createStatusPresenter(QObject* parent)
{
    return new StatusPresenter(parent);
}

QObject* PresentersFactory::createConnectionPresenter(QObject* parent)
{
     return new ConnectionPresenter(m_entry->manager, m_entry->settings, parent);
}

QObject* PresentersFactory::createVideoSettingsPresenter(QObject* parent)
{
    return new VideoSettingsPresenter(m_entry->settings, parent);
}

QObject* PresentersFactory::createNetworkSettingsPresenter(QObject* parent)
{
    return new NetworkSettingsPresenter(m_entry->settings, parent);
}
