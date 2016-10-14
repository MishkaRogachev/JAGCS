#include "video_presenter.h"

// Qt
#include <QCamera>
#include <QCameraInfo>

// Internal
#include "settings_provider.h"
#include "settings.h"

using namespace presentation;

class VideoPresenter::Impl
{
public:
    QCamera* camera;
    QAbstractVideoSurface* videoSurface;

    void updateCameraVideoSurface()
    {
        if (!camera || !videoSurface) return;

        camera->setViewfinder(videoSurface);
        camera->start();
    }
};

VideoPresenter::VideoPresenter(QObject* view):
    BasePresenter(view),
    d(new Impl())
{
    this->updateSource();
}

VideoPresenter::~VideoPresenter()
{
    delete d;
}

QAbstractVideoSurface* VideoPresenter::videoSurface() const
{
    return d->videoSurface;
}

void VideoPresenter::setVideoSurface(QAbstractVideoSurface* videoSurface)
{
    if (d->videoSurface == videoSurface) return;
    d->videoSurface = videoSurface;

    d->updateCameraVideoSurface();
}

void VideoPresenter::updateSource()
{
    if (d->camera) delete d->camera;

    domain::SettingsProvider::beginGroup(domain::video_settings::group);

    QCameraInfo info(domain::SettingsProvider::value(
                         domain::video_settings::device).toByteArray());
    if (info.isNull())
    {
        d->camera = nullptr;
    }
    else
    {
        d->camera = new QCamera(info, this);
        d->updateCameraVideoSurface();
    }

    domain::SettingsProvider::endGroup();
}
