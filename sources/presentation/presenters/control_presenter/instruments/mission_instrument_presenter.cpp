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
    bool updating = false;
};

MissionInstrumentPresenter::MissionInstrumentPresenter(int vehicleId, QObject* parent):
    BaseInstrumentPresenter(parent),
    d(new Impl())
{
    d->service = domain::ServiceRegistry::missionService();
    d->vehicleId = vehicleId;

    connect(d->service, &domain::MissionService::missionItemChanged,
            this, &MissionInstrumentPresenter::updateCurrentWaypoint);
    connect(d->service, &domain::MissionService::missionItemAdded,
            this, &MissionInstrumentPresenter::updateWaypoints);
    connect(d->service, &domain::MissionService::missionItemRemoved,
            this, &MissionInstrumentPresenter::updateWaypoints);
}

MissionInstrumentPresenter::~MissionInstrumentPresenter()
{}

void MissionInstrumentPresenter::updateWaypoints()
{
    d->updating = true;

    QStringList waypoints;
    dao::MissionAssignmentPtr assignment = d->service->vehicleAssignment(d->vehicleId);
    if (assignment)
    {

        dao::MissionPtr mission = d->service->mission(assignment->missionId());

        for (int i = 0; i < mission->count(); ++i)
        {
            waypoints.append(QString::number(i));
        }
    }

    this->setViewsProperty(PROPERTY(waypoints), QVariant::fromValue(waypoints));
    d->updating = false;
}

void MissionInstrumentPresenter::updateCurrentWaypoint()
{
    d->updating = true;

    dao::MissionItemPtr item = d->service->currentWaypoint(d->vehicleId);
    this->setViewsProperty(PROPERTY(waypoint), item ? item->sequence() : -1);
    d->updating = false;
}

void MissionInstrumentPresenter::connectView(QObject* view)
{
    connect(view, SIGNAL(commandSetWaypoint(int)), this, SLOT(onCommandSetWaypoint(int)));

    this->updateWaypoints();
    this->updateCurrentWaypoint();
}

void MissionInstrumentPresenter::onCommandSetWaypoint(int item)
{
    if (d->updating) return;

    d->service->selectCurrentItem(d->vehicleId, item);
}

