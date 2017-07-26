#include "db_facade.h"

// Qt
#include <QDebug>

// Internal
#include "generic_repository.h"
#include "generic_repository_impl.h"

#include "video_source.h"

using namespace db;
using namespace dao;

class DbFacade::Impl
{
public:
    GenericRepository<VideoSource> videoRepository;

    Impl():
        videoRepository("video_sources")
    {}
};

DbFacade::DbFacade(QObject* parent):
    QObject(parent),
    d(new Impl())
{}

DbFacade::~DbFacade()
{}

VideoSourcePtr DbFacade::videoSource(int id, bool reload)
{
    return d->videoRepository.read(id, reload);
}

bool DbFacade::save(const VideoSourcePtr& videoSource)
{
    bool isNew = videoSource->id() == 0;
    if (!d->videoRepository.save(videoSource)) return false;

    emit (isNew ? videoSourceAdded(videoSource) : videoSourceChanged(videoSource));
    return true;
}

bool DbFacade::remove(const VideoSourcePtr& videoSource)
{
    if (!d->videoRepository.remove(videoSource)) return false;
    emit videoSourceRemoved(videoSource);
    return true;
}

VideoSourcePtrList DbFacade::videoSources(const QString& condition, bool reload)
{
    VideoSourcePtrList list;

    for (int id: d->videoRepository.selectId(condition))
    {
        list.append(this->videoSource(id, reload));
    }
    return list;
}
