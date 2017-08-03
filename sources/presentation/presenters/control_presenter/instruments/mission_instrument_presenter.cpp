#include "mission_instrument_presenter.h"

// Qt
#include <QVariant>
#include <QDebug>

// Internal
#include "service_registry.h"
#include "mission_service.h"
#include "mission.h"
#include "mission_assignment.h"
#include "mission_item.h"

using namespace presentation;

class MissionInstrumentPresenter::Impl
{
public:
    domain::MissionService* service;

    int vehicleId = -1;
};

MissionInstrumentPresenter::MissionInstrumentPresenter(int vehicleId, QObject* parent):
    BasePresenter(parent),
    d(new Impl())
{
    d->service = domain::ServiceRegistry::missionService();
    d->vehicleId = vehicleId;

    connect(d->service, &domain::MissionService::missionItemChanged,
            this, &MissionInstrumentPresenter::updateCurrentWaypoint);
}

MissionInstrumentPresenter::~MissionInstrumentPresenter()
{}

void MissionInstrumentPresenter::updateWaypoints()
{
    QStringList waypoints;
    dao::MissionAssignmentPtr assignment = d->service->vehicleAssignment(d->vehicleId);
    if (assignment)
    {
        dao::MissionPtr mission = d->service->mission(assignment->missionId());

        for (int i = 1; i < mission->count(); ++i)
        {
            waypoints.append(QString::number(i));
        }
    }

    this->setViewProperty(PROPERTY(waypoints), QVariant::fromValue(waypoints));
}

void MissionInstrumentPresenter::updateCurrentWaypoint()
{
    dao::MissionItemPtr item = d->service->currentWaypoint(d->vehicleId);
    this->setViewProperty(PROPERTY(waypoint), item ? item->sequence() : -1);
}

void MissionInstrumentPresenter::connectView(QObject* view)
{
    connect(view, SIGNAL(commandSetWaypoint(int)), this, SLOT(onCommandSetWaypoint(int)));

    this->updateWaypoints();
    this->updateCurrentWaypoint();
}

void MissionInstrumentPresenter::onCommandSetWaypoint(int item)
{
    d->service->selectCurrentItem(d->vehicleId, item);
}

