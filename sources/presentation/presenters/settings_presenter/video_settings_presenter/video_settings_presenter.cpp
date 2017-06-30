#include "video_settings_presenter.h"

// Qt
#include <QCameraInfo>
#include <QDebug>

// Internal
#include "db_facade.h"
#include "video_source.h"

#include "video_source_presenter.h"

using namespace presentation;

class VideoSettingsPresenter::Impl
{
public:
    db::DbFacade* facade;

    QList<VideoSourcePresenter*> videoPresenters;
};

VideoSettingsPresenter::VideoSettingsPresenter(db::DbFacade* facade, QObject* parent):
    BasePresenter(parent),
    d(new Impl())
{
    d->facade = facade;

    connect(d->facade, &db::DbFacade::videoSourceAdded,
            this, &VideoSettingsPresenter::onVideoSourceAdded);
    connect(d->facade, &db::DbFacade::videoSourceRemoved,
            this, &VideoSettingsPresenter::onVideoSourceRemoved);

    for (const db::VideoSourcePtr& video: facade->videoSources())
    {
        d->videoPresenters.append(new VideoSourcePresenter(facade, video, this));
    }
}

VideoSettingsPresenter::~VideoSettingsPresenter()
{
    delete d;
}

void VideoSettingsPresenter::connectView(QObject* view)
{
    connect(view, SIGNAL(addDeviceVideo()), this, SLOT(onAddDeviceVideo()));
    connect(view, SIGNAL(addStreamVideo()), this, SLOT(onAddStreamVideo()));

    this->updateCameraInfo();
    this->updateVideoSources();
}

void VideoSettingsPresenter::onVideoSourceAdded(const db::VideoSourcePtr& video)
{
    d->videoPresenters.append(new VideoSourcePresenter(d->facade, video, this));
    this->updateVideoSources();
}

void VideoSettingsPresenter::onVideoSourceRemoved(const db::VideoSourcePtr& video)
{
    for (VideoSourcePresenter* videoPresenter: d->videoPresenters)
    {
        if (videoPresenter->video() != video) continue;

        d->videoPresenters.removeOne(videoPresenter);
        delete videoPresenter;
        this->updateVideoSources();
        return;
    }
}

void VideoSettingsPresenter::updateVideoSources()
{
    QList<QObject*> objectList;
    for (VideoSourcePresenter* videoPresenter: d->videoPresenters)
    {
        objectList.append(videoPresenter);
    }

    this->setViewProperty(PROPERTY(videoSources), QVariant::fromValue(objectList));
}

void VideoSettingsPresenter::updateCameraInfo()
{
    QStringList videoDevices;
    videoDevices.append(QString());

    for (const QCameraInfo& info: QCameraInfo::availableCameras())
    {
        videoDevices.append(info.deviceName());
    }

    this->setViewProperty(PROPERTY(videoDevices), QVariant::fromValue(videoDevices));
}

void VideoSettingsPresenter::onAddDeviceVideo()
{
    db::VideoSourcePtr video = db::VideoSourcePtr::create();
    video->setType(db::VideoSource::Device);
    d->facade->save(video);
}

void VideoSettingsPresenter::onAddStreamVideo()
{
    db::VideoSourcePtr video = db::VideoSourcePtr::create();
    video->setType(db::VideoSource::Stream);
    d->facade->save(video);
}

