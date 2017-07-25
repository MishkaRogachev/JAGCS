#include "mission_status_presenter.h"

// Qt
#include <QVariant>
#include <QDebug>

// Internal
#include "mission_service.h"
#include "mission_assignment.h"
#include "mission.h"

using namespace presentation;

class MissionStatusPresenter::Impl
{
public:
    domain::MissionService* service;

    int vehicleId;
};

MissionStatusPresenter::MissionStatusPresenter(domain::MissionService* service, int vehicleId,
                                               QObject* parent):
    BasePresenter(parent),
    d(new Impl())
{
    d->service = service;
    d->vehicleId = vehicleId;
}

MissionStatusPresenter::~MissionStatusPresenter()
{}

void MissionStatusPresenter::updateView()
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

void MissionStatusPresenter::connectView(QObject* view)
{
    Q_UNUSED(view)

    this->updateView();
}
