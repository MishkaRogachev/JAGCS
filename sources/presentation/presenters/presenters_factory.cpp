#include "presenters_factory.h"

// Internal
#include "video_presenter.h"
#include "map_presenter.h"

#include "status_presenter.h"
#include "connection_presenter.h"

#include "video_settings_presenter.h"
#include "network_settings_presenter.h"

using namespace presentation;

PresentersFactory::PresentersFactory(
        domain::SettingsProvider* settings, QObject* parent):
    QObject(parent),
    m_settings(settings)
{}

QObject* PresentersFactory::createVideoPresenter(QObject* parent)
{
    return new VideoPresenter(m_settings, parent);
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
     return new ConnectionPresenter(nullptr, m_settings, parent); // TODO: DomainEntry
}

QObject* PresentersFactory::createVideoSettingsPresenter(QObject* parent)
{
    return new VideoSettingsPresenter(m_settings, parent);
}

QObject* PresentersFactory::createNetworkSettingsPresenter(QObject* parent)
{
    return new NetworkSettingsPresenter(m_settings, parent);
}
