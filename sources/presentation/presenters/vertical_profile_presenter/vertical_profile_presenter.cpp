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
{}

void VerticalProfilePresenter::showMission(const db::MissionPtr& mission)
{
    this->invokeViewMethod(PROPERTY(clearWaypoints));

    if (mission.isNull()) return;
    QGeoCoordinate lastCoordinate;
    int distance = 0;
    for (const db::MissionItemPtr& item: m_dbFacade->missionItems(mission->id()))
    {
        // FIXME: relative altitude
        this->invokeViewMethod(PROPERTY(appendWaypoint), distance, item->altitude());

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
    }
}

void VerticalProfilePresenter::clearMission()
{
    this->invokeViewMethod(METHOD(clearWaypoints));
}

void VerticalProfilePresenter::connectView(QObject* view)
{
    Q_UNUSED(view)
}
