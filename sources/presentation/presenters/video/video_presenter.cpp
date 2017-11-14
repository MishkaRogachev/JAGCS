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
    dao::VideoSourcePtr video;
    VideoProvider provider;
    QMediaObject* media = nullptr;
};

VideoPresenter::VideoPresenter(QObject* parent):
    BasePresenter(parent),
    d(new Impl())
{}

VideoPresenter::~VideoPresenter()
{}

dao::VideoSourcePtr VideoPresenter::video() const
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
    case dao::VideoSource::Device:
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
    case dao::VideoSource::Stream:
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

void VideoPresenter::setVideo(const dao::VideoSourcePtr& video)
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
