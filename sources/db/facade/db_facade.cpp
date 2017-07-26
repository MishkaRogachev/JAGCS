#include "db_facade.h"

// Qt
#include <QDebug>

// Internal
#include "generic_repository.h"
#include "generic_repository_impl.h"

#include "link_description.h"
#include "video_source.h"

using namespace db;
using namespace dao;

class DbFacade::Impl
{
public:
    GenericRepository<LinkDescription> linkRepository;
    GenericRepository<VideoSource> videoRepository;

    Impl():
        linkRepository("links"),
        videoRepository("video_sources")
    {}
};

DbFacade::DbFacade(QObject* parent):
    QObject(parent),
    d(new Impl())
{}

DbFacade::~DbFacade()
{}

LinkDescriptionPtr DbFacade::link(int id, bool reload)
{
    return d->linkRepository.read(id, reload);
}

VideoSourcePtr DbFacade::videoSource(int id, bool reload)
{
    return d->videoRepository.read(id, reload);
}

bool DbFacade::save(const LinkDescriptionPtr& link)
{
    bool isNew = link->id() == 0;
    if (!d->linkRepository.save(link)) return false;

    emit (isNew ? linkAdded(link) : linkChanged(link));
    return true;
}

bool DbFacade::save(const VideoSourcePtr& videoSource)
{
    bool isNew = videoSource->id() == 0;
    if (!d->videoRepository.save(videoSource)) return false;

    emit (isNew ? videoSourceAdded(videoSource) : videoSourceChanged(videoSource));
    return true;
}

bool DbFacade::remove(const LinkDescriptionPtr& link)
{
    if (!d->linkRepository.remove(link)) return false;
    emit linkRemoved(link);
    return true;
}

bool DbFacade::remove(const VideoSourcePtr& videoSource)
{
    if (!d->videoRepository.remove(videoSource)) return false;
    emit videoSourceRemoved(videoSource);
    return true;
}

LinkDescriptionPtrList DbFacade::links(const QString& condition, bool reload)
{
    LinkDescriptionPtrList list;

    for (int id: d->linkRepository.selectId(condition))
    {
        list.append(this->link(id, reload));
    }

    return list;
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

void DbFacade::clearAll()
{
    d->linkRepository.clear();
    d->videoRepository.clear();
}
