#include "abstract_map_presenter.h"

// Qt
#include <QDebug>

// Internal
#include "service_registry.h"

#include "command_service.h"

#include "mission_service.h"
#include "mission_item.h"

using namespace presentation;

class AbstractMapPresenter::Impl
{
public:
    domain::CommandService* commandService = serviceRegistry->commandService();
    domain::MissionService* missionService = serviceRegistry->missionService();
};

AbstractMapPresenter::AbstractMapPresenter(QObject* object):
    BasePresenter(object),
    d(new Impl())
{}

AbstractMapPresenter::~AbstractMapPresenter()
{}

void AbstractMapPresenter::moveItem(int itemId, double latitude, double longitude)
{
    dto::MissionItemPtr item = d->missionService->missionItem(itemId);

    item->setLatitude(latitude);
    item->setLongitude(longitude);
    item->setStatus(dto::MissionItem::NotActual);

    d->missionService->save(item);
}

void AbstractMapPresenter::navTo(int vehicleId, double latitude, double longitude, float altitude)
{
    dto::CommandPtr command = dto::CommandPtr::create();

    command->setType(dto::Command::NavTo);
    command->setArguments( { latitude, longitude, altitude} );

    d->commandService->executeCommand(vehicleId, command);
}
