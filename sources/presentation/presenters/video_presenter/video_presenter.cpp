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
    domain::SettingsProvider* settings;
    QCamera* camera;
    QAbstractVideoSurface* videoSurface;

    void updateCameraVideoSurface()
    {
        if (!camera || !videoSurface) return;

        camera->setViewfinder(videoSurface);
        camera->start();
    }
};

VideoPresenter::VideoPresenter(
        domain::SettingsProvider* settings, QObject* view):
    BasePresenter(view),
    d(new Impl())
{
    d->settings = settings;

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

    d->settings->beginGroup(domain::video_settings::group);

    QCameraInfo info(d->settings->value(domain::video_settings::device).toByteArray());
    if (info.isNull())
    {
        d->camera = nullptr;
    }
    else
    {
        d->camera = new QCamera(info, this);
        d->updateCameraVideoSurface();
    }

    d->settings->endGroup();
}
