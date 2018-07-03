#include "active_video_presenter.h"

// Qt
#include <QDebug>

// Internal
#include "settings_provider.h"

#include "service_registry.h"
#include "video_service.h"

using namespace presentation;

ActiveVideoPresenter::ActiveVideoPresenter(QObject* parent):
    VideoPresenter(parent)
{}

void ActiveVideoPresenter::setActiveVideo(int videoId)
{
    this->setVideo(serviceRegistry->videoService()->videoSource(videoId));
}

void ActiveVideoPresenter::updateActiveVideo()
{
    this->setActiveVideo(settings::Provider::value(settings::video::activeVideo).toInt());
}
