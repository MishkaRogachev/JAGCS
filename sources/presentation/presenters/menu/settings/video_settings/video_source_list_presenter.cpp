#include "video_source_list_presenter.h"

// Qt
#include <QCameraInfo>
#include <QDebug>

// Internal
#include "settings_provider.h"

#include "video_source.h"

#include "service_registry.h"
#include "video_service.h"

using namespace presentation;

VideoSourceListPresenter::VideoSourceListPresenter(QObject* parent):
    BasePresenter(parent),
    m_service(serviceRegistry->videoService())
{
    connect(m_service, &domain::VideoService::videoSourceAdded,
            this, &VideoSourceListPresenter::updateVideoSources);
    connect(m_service, &domain::VideoService::videoSourceRemoved,
            this, &VideoSourceListPresenter::updateVideoSources);
}

void VideoSourceListPresenter::updateVideoSources()
{
    QVariantList videoSourceIds;
    for (const dto::VideoSourcePtr& videoSource: m_service->videoSources())
    {
        videoSourceIds.append(videoSource->id());
    }

    this->setViewProperty(PROPERTY(videoSourceIds), QVariant::fromValue(videoSourceIds));
    this->setViewProperty(PROPERTY(activeVideo),
                          settings::Provider::value(settings::video::activeVideo).toInt());
}

void VideoSourceListPresenter::updateCameraInfo()
{
    QStringList videoDevices;
    videoDevices.append(QString());

    for (const QCameraInfo& info: QCameraInfo::availableCameras())
    {
        videoDevices.append(info.deviceName());
    }

    this->setViewProperty(PROPERTY(videoDevices), QVariant::fromValue(videoDevices));
}

void VideoSourceListPresenter::addDeviceVideo()
{
    dto::VideoSourcePtr video = dto::VideoSourcePtr::create();
    video->setType(dto::VideoSource::Device);
    m_service->save(video);
}

void VideoSourceListPresenter::addStreamVideo()
{
    dto::VideoSourcePtr video = dto::VideoSourcePtr::create();
    video->setType(dto::VideoSource::Stream);
    m_service->save(video);
}

void VideoSourceListPresenter::saveActiveVideo(int video)
{
    settings::Provider::setValue(settings::video::activeVideo, video);
}
