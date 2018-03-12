#include "video_presenter.h"

// Qt
#include <QCamera>
#include <QCameraInfo>
#include <QMediaPlayer>
#include <QDebug>

// Internal
#include "video_source.h"

#include "service_registry.h"
#include "video_service.h"

#include "video_provider.h"

using namespace presentation;

class VideoPresenter::Impl
{
public:
    dto::VideoSourcePtr video;
    VideoProvider provider;
    QMediaObject* media = nullptr;
};

VideoPresenter::VideoPresenter(QObject* parent):
    BasePresenter(parent),
    d(new Impl())
{
    connect(serviceRegistry->videoService(),
            &domain::VideoService::videoSourceChanged,
            this, &VideoPresenter::onVideoSourceChanged);
    connect(serviceRegistry->videoService(),
            &domain::VideoService::videoSourceRemoved,
            this, &VideoPresenter::onVideoSourceRemoved);
}

VideoPresenter::~VideoPresenter()
{}

dto::VideoSourcePtr VideoPresenter::video() const
{
    return d->video;
}

void VideoPresenter::updateSource()
{
    if (d->media)
    {
        delete d->media;
        d->media = nullptr;
    }

    if (!d->provider.videoSurface() || d->video.isNull()) return;

    switch (d->video->type()) { // TODO: media factory
    case dto::VideoSource::Device:
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
    case dto::VideoSource::Stream:
    {
        QMediaPlayer* player = new QMediaPlayer(this);
        player->setMedia(QUrl(d->video->source()));
        player->setVideoOutput(d->provider.videoSurface());
        player->play();
        connect(player,
                static_cast<void(QMediaPlayer::*)(QMediaPlayer::Error)>(&QMediaPlayer::error),
                player, [player](QMediaPlayer::Error error) {
            if (error == QMediaPlayer::NetworkError ||
                error == QMediaPlayer::ResourceError)
                player->play();
        });
        d->media = player;
        break;
    }
    default:
        break;
    }
}

void VideoPresenter::setVideo(const dto::VideoSourcePtr& video)
{
    if (d->video == video) return;

    d->video = video;
    this->updateSource();
}

void VideoPresenter::connectView(QObject* view)
{
    view->setProperty(PROPERTY(videoSource), QVariant::fromValue(&d->provider));

    this->updateSource();
}

void VideoPresenter::disconnectView(QObject* view)
{
    Q_UNUSED(view)

    if (d->media)
    {
        delete d->media;
        d->media = nullptr;
    }
}

void VideoPresenter::onVideoSourceChanged(const dto::VideoSourcePtr& video)
{
    if (d->video == video) this->updateSource();
}

void VideoPresenter::onVideoSourceRemoved(const dto::VideoSourcePtr& video)
{
    if (d->video != video) return;

    d->video.clear();
    this->updateSource();
}
