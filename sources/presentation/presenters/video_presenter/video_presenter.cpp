#include "video_presenter.h"

// Qt
#include <QCamera>
#include <QCameraInfo>
#include <QMediaPlayer>
#include <QDebug>

// Internal
#include "video_source.h"

#include "video_provider.h"

using namespace presentation;

class VideoPresenter::Impl
{
public:
    db::VideoSourcePtr video;
    VideoProvider provider;
    QMediaObject* media = nullptr;
};

VideoPresenter::VideoPresenter(const db::VideoSourcePtr& video, QObject* parent):
    BasePresenter(parent),
    d(new Impl())
{
    d->video = video;
}

VideoPresenter::~VideoPresenter()
{}

void VideoPresenter::updateSource()
{
    if (d->media)
    {
        delete d->media;
        d->media = nullptr;
    }

    switch (d->video->type()) { // TODO: media factory
    case db::VideoSource::Device:
    {
        QCameraInfo info(d->video->source().toUtf8());
        if (!info.isNull())
        {
            QCamera* camera = new QCamera(info, this);
            camera->setViewfinder(d->provider.videoSurface());
            camera->start();
            d->media = camera;
        }
        break;
    }
    case db::VideoSource::Stream:
    {
        QMediaPlayer* player = new QMediaPlayer(this);
        player->setMedia(QUrl(d->video->source()));
        d->media = player;
        break;
    }
    default:
        break;
    }
}

void VideoPresenter::connectView(QObject* view)
{
    view->setProperty(PROPERTY(videoSource), QVariant::fromValue(&d->provider));
    this->updateSource();
}
