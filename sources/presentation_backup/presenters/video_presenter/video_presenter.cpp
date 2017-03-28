#include "video_presenter.h"

// Qt
#include <QCamera>
#include <QCameraInfo>
#include <QDebug>

// Internal
#include "settings_provider.h"
#include "settings.h"

#include "video_provider.h"

using namespace presentation;

class VideoPresenter::Impl
{
public:
    QCamera* camera;

    VideoProvider provider;

    void updateCameraVideoSurface()
    {
        if (!camera || !provider.videoSurface()) return;

        camera->setViewfinder(provider.videoSurface());
        camera->start();
    }
};

VideoPresenter::VideoPresenter(QObject* parent):
    BasePresenter(parent),
    d(new Impl())
{
    this->updateSource();
}

VideoPresenter::~VideoPresenter()
{
    delete d;
}

void VideoPresenter::updateSource()
{
    if (d->camera) delete d->camera;

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
}

void VideoPresenter::connectView(QObject* view)
{
    view->setProperty(PROPERTY(videoSource), QVariant::fromValue(&d->provider));
    d->updateCameraVideoSurface();
}
