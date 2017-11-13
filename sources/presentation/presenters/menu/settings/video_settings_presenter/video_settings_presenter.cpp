#include "video_settings_presenter.h"

// Qt
#include <QCameraInfo>
#include <QDebug>

// Internal
#include "service_registry.h"
#include "video_service.h"
#include "video_source.h"

#include "video_source_presenter.h"

using namespace presentation;

class VideoSettingsPresenter::Impl
{
public:
    domain::VideoService* service;

    QList<VideoSourcePresenter*> videoPresenters;
};

VideoSettingsPresenter::VideoSettingsPresenter(QObject* parent):
    BasePresenter(parent),
    d(new Impl())
{
    d->service = domain::ServiceRegistry::videoService();

    connect(d->service, &domain::VideoService::videoSourceAdded,
            this, &VideoSettingsPresenter::onVideoSourceAdded);
    connect(d->service, &domain::VideoService::videoSourceRemoved,
            this, &VideoSettingsPresenter::onVideoSourceRemoved);

    for (const dao::VideoSourcePtr& video: d->service->videoSources())
    {
        d->videoPresenters.append(new VideoSourcePresenter(d->service, video, this));
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

void VideoSettingsPresenter::onVideoSourceAdded(const dao::VideoSourcePtr& video)
{
    d->videoPresenters.append(new VideoSourcePresenter(d->service, video, this));
    this->updateVideoSources();
}

void VideoSettingsPresenter::onVideoSourceRemoved(const dao::VideoSourcePtr& video)
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
    dao::VideoSourcePtr video = dao::VideoSourcePtr::create();
    video->setType(dao::VideoSource::Device);
    d->service->save(video);
}

void VideoSettingsPresenter::onAddStreamVideo()
{
    dao::VideoSourcePtr video = dao::VideoSourcePtr::create();
    video->setType(dao::VideoSource::Stream);
    d->service->save(video);
}

