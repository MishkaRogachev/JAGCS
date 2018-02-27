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
    m_service(domain::ServiceRegistry::videoService())
{
    connect(m_service, &domain::VideoService::videoSourceAdded,
            this, &VideoSourceListPresenter::updateVideoSources);
    connect(m_service, &domain::VideoService::videoSourceRemoved,
            this, &VideoSourceListPresenter::updateVideoSources);
}

void VideoSourceListPresenter::updateVideoSources()
{
    QVariantList videoSourceIds;
    for (const dao::VideoSourcePtr& videoSource: m_service->videoSources())
    {
        videoSourceIds.append(videoSource->id());
    }

    this->setViewProperty(PROPERTY(videoSourceIds), QVariant::fromValue(videoSourceIds));
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
    dao::VideoSourcePtr video = dao::VideoSourcePtr::create();
    video->setType(dao::VideoSource::Device);
    m_service->save(video);
}

void VideoSourceListPresenter::addStreamVideo()
{
    dao::VideoSourcePtr video = dao::VideoSourcePtr::create();
    video->setType(dao::VideoSource::Stream);
    m_service->save(video);
}

void VideoSourceListPresenter::setActiveVideo(int video)
{
    settings::Provider::setValue(settings::video::activeVideo, video);
    this->setViewProperty(PROPERTY(activeVideo), video);
}

void VideoSourceListPresenter::connectView(QObject* view)
{
    view->setProperty(PROPERTY(activeVideo),
                      settings::Provider::value(settings::video::activeVideo).toInt());
}
