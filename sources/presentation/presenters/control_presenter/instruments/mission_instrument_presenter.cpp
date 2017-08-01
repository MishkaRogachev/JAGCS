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
    int currentWaypoint = 0;
};

MissionInstrumentPresenter::MissionInstrumentPresenter(int vehicleId, QObject* parent):
    BasePresenter(parent),
    d(new Impl())
{
    d->service = domain::ServiceRegistry::missionService();
    d->vehicleId = vehicleId;

    connect(d->service, &domain::MissionService::missionItemChanged,
            this, [this](const dao::MissionItemPtr& item) {
        if (!item->isCurrent()) return;
        dao::MissionAssignmentPtr assignment = d->service->vehicleAssignment(d->vehicleId);
        if (assignment && item->missionId() == assignment->missionId())
        {
            d->currentWaypoint = item->sequence();
            this->updateCurrentWaypoint();
        }
    });
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
    this->setViewProperty(PROPERTY(waypoint), d->currentWaypoint);
}

void MissionInstrumentPresenter::connectView(QObject* view)
{
    connect(view, SIGNAL(commandSetWaypoint(int)), this, SLOT(onCommandSetWaypoint(int)));

    this->updateWaypoints();
    this->updateCurrentWaypoint();
}

void MissionInstrumentPresenter::onCommandSetWaypoint(int item)
{
    d->service->setCurrent(d->vehicleId, item);
}

