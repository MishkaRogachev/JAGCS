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

void ActiveVideoPresenter::updateActiveVideo()
{
    dto::VideoSourcePtr video;
    int videoId = settings::Provider::value(settings::video::activeVideo).toInt();
    if (videoId > -1)
    {
        video = serviceRegistry->videoService()->videoSource(
                    settings::Provider::value(settings::video::activeVideo).toInt());
    }
    this->setVideo(video);
}
