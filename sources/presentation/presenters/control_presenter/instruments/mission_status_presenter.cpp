#include "mission_status_presenter.h"

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

class MissionStatusPresenter::Impl
{
public:
    domain::MissionService* service;

    int vehicleId = -1;
    int currentWaypoint = 0;
};

MissionStatusPresenter::MissionStatusPresenter(int vehicleId, QObject* parent):
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

MissionStatusPresenter::~MissionStatusPresenter()
{}

void MissionStatusPresenter::updateWaypoints()
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

void MissionStatusPresenter::updateCurrentWaypoint()
{
    this->setViewProperty(PROPERTY(waypoint), d->currentWaypoint);
}

void MissionStatusPresenter::connectView(QObject* view)
{
    Q_UNUSED(view)

    this->updateWaypoints();
    this->updateCurrentWaypoint();
}
