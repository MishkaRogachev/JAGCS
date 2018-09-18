#include "video_service.h"

// Qt
#include <QDebug>

// Internal
#include "generic_db_repository.h"

#include "video_source.h"

using namespace dto;
using namespace domain;

class VideoService::Impl
{
public:
    GenericDbRepository<VideoSource> videoRepository;

    Impl():
        videoRepository("video_sources")
    {}

    void loadVideoSources(const QString& condition = QString())
    {
        for (int id: videoRepository.selectId(condition)) videoRepository.read(id);
    }
};

VideoService::VideoService(QObject* parent):
    QObject(parent),
    d(new Impl())
{
    qRegisterMetaType<dto::VideoSourcePtr>("dto::VideoSourcePtr");

    d->loadVideoSources();
}

VideoService::~VideoService()
{}

VideoSourcePtr VideoService::videoSource(int id) const
{
    return d->videoRepository.read(id);
}

VideoSourcePtrList VideoService::videoSources() const
{
    return d->videoRepository.loadedEntities();
}


bool VideoService::save(const VideoSourcePtr& videoSource)
{
    bool isNew = videoSource->id() == 0;
    if (!d->videoRepository.save(videoSource)) return false;

    emit (isNew ? videoSourceAdded(videoSource) : videoSourceChanged(videoSource));
    return true;
}

bool VideoService::remove(const VideoSourcePtr& videoSource)
{
    if (!d->videoRepository.remove(videoSource)) return false;
    emit videoSourceRemoved(videoSource);
    return true;
}
