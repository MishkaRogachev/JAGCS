#include "video_source_list_presenter.h"

// Qt
#include <QSortFilterProxyModel>
#include <QCameraInfo>
#include <QDebug>

// Internal
#include "settings_provider.h"

#include "video_source.h"

#include "service_registry.h"
#include "video_service.h"

#include "video_source_list_model.h"

using namespace presentation;

class VideoSourceListPresenter::Impl
{
public:
    domain::VideoService* const service = serviceRegistry->videoService();

    VideoSourceListModel videosModel;
    QSortFilterProxyModel filterModel;
};

VideoSourceListPresenter::VideoSourceListPresenter(QObject* parent):
    BasePresenter(parent),
    d(new Impl())
{
    d->filterModel.setSourceModel(&d->videosModel);
    d->filterModel.setFilterRole(VideoSourceListModel::VideoNameRole);
    d->filterModel.setSortRole(VideoSourceListModel::VideoNameRole);
    d->filterModel.setDynamicSortFilter(true);
    d->filterModel.sort(0, Qt::AscendingOrder);

    d->videosModel.setVideos(d->service->videoSources());

    connect(d->service, &domain::VideoService::videoSourceAdded,
            &d->videosModel, &VideoSourceListModel::addVideo);
    connect(d->service, &domain::VideoService::videoSourceRemoved,
            &d->videosModel, &VideoSourceListModel::removeVideo);
    connect(d->service, &domain::VideoService::videoSourceChanged,
            &d->videosModel, &VideoSourceListModel::updateVideo);
}

VideoSourceListPresenter::~VideoSourceListPresenter()
{}

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
    d->service->save(video);
}

void VideoSourceListPresenter::addStreamVideo()
{
    dto::VideoSourcePtr video = dto::VideoSourcePtr::create();
    video->setType(dto::VideoSource::Stream);
    d->service->save(video);
}

void VideoSourceListPresenter::saveActiveVideo(int video)
{
    settings::Provider::setValue(settings::video::activeVideo, video);
}

void VideoSourceListPresenter::filter(const QString& filterString)
{
    d->filterModel.setFilterFixedString(filterString);
}

void VideoSourceListPresenter::connectView(QObject* view)
{
    this->updateCameraInfo();

    view->setProperty(PROPERTY(videos), QVariant::fromValue(&d->filterModel));
    this->setViewProperty(PROPERTY(activeVideo),
                          settings::Provider::value(settings::video::activeVideo).toInt());
}
