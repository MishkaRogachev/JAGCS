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

    dao::MissionAssignmentPtr assignment;
    bool updating = false;
};

MissionInstrumentPresenter::MissionInstrumentPresenter(int vehicleId, QObject* parent):
    BaseInstrumentPresenter(parent),
    d(new Impl())
{
    d->service = domain::ServiceRegistry::missionService();
    d->assignment = d->service->vehicleAssignment(vehicleId);

    connect(d->service, &domain::MissionService::missionItemChanged,
            this, &MissionInstrumentPresenter::updateCurrentWaypoint);
    connect(d->service, &domain::MissionService::missionItemAdded,
            this, &MissionInstrumentPresenter::updateWaypoints);
    connect(d->service, &domain::MissionService::missionItemRemoved,
            this, &MissionInstrumentPresenter::updateWaypoints);
    connect(d->service, &domain::MissionService::assignmentChanged,
            this, [this](const dao::MissionAssignmentPtr& assignment) {
        if (d->assignment.isNull() || d->assignment != assignment) return;

        this->setViewsProperty(PROPERTY(downloading), bool(d->assignment->status() ==
                               dao::MissionAssignment::Downloading));
    });
}

MissionInstrumentPresenter::~MissionInstrumentPresenter()
{}

void MissionInstrumentPresenter::updateWaypoints()
{
    d->updating = true;

    QStringList waypoints;
    if (d->assignment)
    {
        dao::MissionPtr mission = d->service->mission(d->assignment->missionId());

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
    if (d->assignment.isNull()) return;
    d->updating = true;

    dao::MissionItemPtr item = d->service->currentWaypoint(d->assignment->vehicleId());
    this->setViewsProperty(PROPERTY(waypoint), item ? item->sequence() : -1);
    d->updating = false;
}

void MissionInstrumentPresenter::onDownloadMission()
{
    if (d->assignment) d->service->download(d->assignment);
}

void MissionInstrumentPresenter::onCancelSyncMission()
{
    if (d->assignment) d->service->cancelSync(d->assignment);
}

void MissionInstrumentPresenter::connectView(QObject* view)
{
    connect(view, SIGNAL(commandSetWaypoint(int)), this, SLOT(onCommandSetWaypoint(int)));
    connect(view, SIGNAL(downloadMission()), this, SLOT(onDownloadMission()));
    connect(view, SIGNAL(cancelSyncMission()), this, SLOT(onCancelSyncMission()));

    this->updateWaypoints();
    this->updateCurrentWaypoint();
}

void MissionInstrumentPresenter::onCommandSetWaypoint(int item)
{
    if (d->updating || d->assignment.isNull()) return;

    d->service->selectCurrentItem(d->assignment->vehicleId(), item);
}

