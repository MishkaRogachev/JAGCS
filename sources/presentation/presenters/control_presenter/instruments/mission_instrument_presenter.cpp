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
    connect(d->service, &domain::MissionService::missionItemAdded,
            this, &MissionInstrumentPresenter::updateWaypoints);
    connect(d->service, &domain::MissionService::missionItemRemoved,
            this, &MissionInstrumentPresenter::updateWaypoints);
}

MissionInstrumentPresenter::~MissionInstrumentPresenter()
{}

void MissionInstrumentPresenter::updateWaypoints()
{
    this->setViewConnected(false);

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

    this->setViewProperty(PROPERTY(waypoints), QVariant::fromValue(waypoints));
    this->setViewConnected(true);
}

void MissionInstrumentPresenter::updateCurrentWaypoint()
{
    this->setViewConnected(false);

    dao::MissionItemPtr item = d->service->currentWaypoint(d->vehicleId);
    this->setViewProperty(PROPERTY(waypoint), item ? item->sequence() : -1);
    this->setViewConnected(true);
}

void MissionInstrumentPresenter::connectView(QObject* view)
{
    Q_UNUSED(view)

    this->updateWaypoints();
    this->updateCurrentWaypoint();
}

void MissionInstrumentPresenter::setViewConnected(bool connected)
{
    if (connected)
    {
        connect(this->view(), SIGNAL(commandSetWaypoint(int)), this, SLOT(onCommandSetWaypoint(int)));
    }
    else
    {
        disconnect(this->view(), 0, this, 0);
    }
}

void MissionInstrumentPresenter::onCommandSetWaypoint(int item)
{
    d->service->selectCurrentItem(d->vehicleId, item);
}

