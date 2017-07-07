#include "mission_status_presenter.h"

// Qt
#include <QVariant>
#include <QDebug>

// Internal
#include "db_facade.h"
#include "mission_assignment.h"
#include "mission.h"

using namespace presentation;

class MissionStatusPresenter::Impl
{
public:
    db::DbFacade* facade;

    int vehicleId;
};

MissionStatusPresenter::MissionStatusPresenter(db::DbFacade* facade, int vehicleId,
                                               QObject* parent):
    BasePresenter(parent),
    d(new Impl())
{
    d->facade = facade;
    d->vehicleId = vehicleId;
}

MissionStatusPresenter::~MissionStatusPresenter()
{}

void MissionStatusPresenter::updateView()
{
    QStringList waypoints;
    db::MissionAssignmentPtr assignment = d->facade->vehicleAssignment(d->vehicleId);
    if (assignment)
    {
        db::MissionPtr mission = d->facade->mission(assignment->missionId());

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
