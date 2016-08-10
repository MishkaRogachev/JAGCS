#include "presenters_factory.h"

// Internal
#include "status_presenter.h"
#include "video_presenter.h"
#include "network_settings_presenter.h"

using namespace presentation;

PresentersFactory::PresentersFactory(SettingsProvider* settings, QObject* parent):
    QObject(parent),
    m_settings(settings)
{}

QObject* PresentersFactory::createStatusPresenter(QObject* parent)
{
    return new StatusPresenter(parent);
}

QObject* PresentersFactory::createVideoPresenter(QObject* parent)
{
    return new VideoPresenter(parent);
}

QObject* PresentersFactory::createNetworkSettingsPresenter(QObject* parent)
{
    return new NetworkSettingsPresenter(m_settings, parent);
}
