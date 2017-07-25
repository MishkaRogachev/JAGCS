#include "db_facade.h"

// Qt
#include <QDebug>

// Internal
#include "generic_repository.h"
#include "generic_repository_impl.h"

#include "mission.h"
#include "mission_item.h"
#include "mission_assignment.h"
#include "vehicle.h"
#include "link_description.h"
#include "video_source.h"

using namespace db;
using namespace dao;

class DbFacade::Impl
{
public:
    GenericRepository<Vehicle> vehicleRepository;
    GenericRepository<LinkDescription> linkRepository;
    GenericRepository<VideoSource> videoRepository;

    Impl():
        vehicleRepository("vehicles"),
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

VehiclePtr DbFacade::vehicle(int id, bool reload)
{
    return d->vehicleRepository.read(id, reload);
}

LinkDescriptionPtr DbFacade::link(int id, bool reload)
{
    return d->linkRepository.read(id, reload);
}

VideoSourcePtr DbFacade::videoSource(int id, bool reload)
{
    return d->videoRepository.read(id, reload);
}

bool DbFacade::save(const VehiclePtr& vehicle)
{
    bool isNew = vehicle->id() == 0;
    if (!d->vehicleRepository.save(vehicle)) return false;

    emit (isNew ? vehicleAdded(vehicle) : vehicleChanged(vehicle));
    return true;
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

bool DbFacade::remove(const VehiclePtr& vehicle)
{
    // FIXME: remove assignment on vehicle remove
    //MissionAssignmentPtr assignment = this->vehicleAssignment(vehicle->id());
    //if (assignment && !this->remove(assignment)) return false;

    if (!d->vehicleRepository.remove(vehicle)) return false;
    emit vehicleRemoved(vehicle);
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

VehiclePtrList DbFacade::vehicles(const QString& condition, bool reload)
{
    VehiclePtrList list;

    for (int id: d->vehicleRepository.selectId(condition))
    {
        list.append(this->vehicle(id, reload));
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

int DbFacade::vehicleIdByMavId(int mavId) const
{
    for (int id: d->vehicleRepository.selectId(QString("mavId = %1").arg(mavId)))
        return id;
    return 0;
}

void DbFacade::clearAll()
{
    d->vehicleRepository.clear();
    d->linkRepository.clear();
    d->videoRepository.clear();
}
