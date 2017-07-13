#include "vertical_profile_presenter.h"

// Qt
#include <QGeoCoordinate>
#include <QVariant>
#include <QDebug>

// Internal
#include "db_facade.h"
#include "mission.h"
#include "mission_item.h"

using namespace presentation;

VerticalProfilePresenter::VerticalProfilePresenter(db::DbFacade* dbFacade, QObject* parent):
    BasePresenter(parent),
    m_dbFacade(dbFacade)
{
    connect(m_dbFacade, &db::DbFacade::missionItemAdded, this, [this]
            (const db::MissionItemPtr& missionItem){
        if (m_mission && m_mission->id() == missionItem->missionId()) this->updateMission();
    });

    connect(m_dbFacade, &db::DbFacade::missionItemRemoved, this, [this]
            (const db::MissionItemPtr& missionItem){
        if (m_mission && m_mission->id() == missionItem->missionId()) this->updateMission();
    });

    connect(m_dbFacade, &db::DbFacade::missionItemChanged, this, [this]
            (const db::MissionItemPtr& missionItem){
        if (m_mission && m_mission->id() == missionItem->missionId()) this->updateMission();
    });
}

void VerticalProfilePresenter::selectMission(const db::MissionPtr& mission)
{
    if (m_mission == mission) return;

    m_mission = mission;
    if (this->view()) this->updateMission();
}

void VerticalProfilePresenter::updateMission()
{
    this->invokeViewMethod(PROPERTY(clearWaypoints));

    if (m_mission.isNull()) return;
    QGeoCoordinate lastCoordinate;
    int distance = 0;
    for (const db::MissionItemPtr& item: m_dbFacade->missionItems(m_mission->id()))
    {
        // TODO: another commands
        if (item->command() == db::MissionItem::Waypoint)
        {
            QGeoCoordinate coordinate(item->latitude(), item->longitude());
            qDebug() << coordinate;
            if (lastCoordinate.isValid() && coordinate.isValid())
            {
                qDebug() << lastCoordinate.distanceTo(coordinate);
                distance += lastCoordinate.distanceTo(coordinate);
            }
            lastCoordinate = coordinate;
        }

        // FIXME: relative altitude
        this->invokeViewMethod(PROPERTY(appendWaypoint), distance, item->altitude());
    }
}

void VerticalProfilePresenter::clearMission()
{
    this->invokeViewMethod(METHOD(clearWaypoints));
}

void VerticalProfilePresenter::connectView(QObject* view)
{
    Q_UNUSED(view)

    this->updateMission();
}
