#include "vertical_profile_presenter.h"

// Qt
#include <QVariant>
#include <QDebug>

// Internal
#include "service_registry.h"
#include "mission_service.h"

#include "mission.h"
#include "mission_item.h"

using namespace presentation;

VerticalProfilePresenter::VerticalProfilePresenter(QObject* parent):
    BasePresenter(parent),
    m_service(serviceRegistry->missionService())
{
    connect(m_service, &domain::MissionService::missionItemAdded, this, [this]
            (const dto::MissionItemPtr& missionItem) {
        if (m_missionId == missionItem->missionId()) this->updateMission();
    });
    connect(m_service, &domain::MissionService::missionItemRemoved, this, [this]
            (const dto::MissionItemPtr& missionItem) {
        if (m_missionId == missionItem->missionId()) this->updateMission();
    });
    connect(m_service, &domain::MissionService::missionItemChanged, this, [this]
            (const dto::MissionItemPtr& missionItem) {
        if (m_missionId == missionItem->missionId()) this->updateMission();
    });
    connect(m_service, &domain::MissionService::missionRemoved, this, [this]
            (const dto::MissionPtr& mission) {
        if (m_missionId == mission->id()) this->setMission(0);
    });
}

void VerticalProfilePresenter::setMission(int missionId)
{
    if (m_missionId == missionId) return;

    m_missionId = missionId;
    this->updateMission();
}

void VerticalProfilePresenter::updateMission()
{
    this->invokeViewMethod(PROPERTY(clearWaypoints));

    dto::MissionPtr mission = m_service->mission(m_missionId);
    if (mission.isNull() || mission->count() < 1) return;

    QGeoCoordinate lastPosition;
    int distance = 0;
    int homeAltitude = 0;
    int minAltitude = INT_MAX;
    int maxAltitude = INT_MIN;

    for (const dto::MissionItemPtr& item: m_service->missionItems(mission->id()))
    {
        if (!item->isAltitudedItem()) continue;

        if (item->sequence() == 0) homeAltitude = item->altitude();

        if (item->isPositionatedItem())
        {
            if (item->coordinate().isValid() && lastPosition.isValid())
            {
                distance += lastPosition.distanceTo(item->coordinate());
            }
            lastPosition = item->coordinate();
        }

        int altitude = item->isAltitudeRelative() ? homeAltitude + item->altitude() : item->altitude();

        if (altitude < minAltitude) minAltitude = altitude;
        if (altitude > maxAltitude) maxAltitude = altitude;

        this->invokeViewMethod(PROPERTY(appendWaypoint), distance, altitude);
    }

    this->setViewProperty(PROPERTY(minDistance), 0);
    this->setViewProperty(PROPERTY(maxDistance), distance);
    this->setViewProperty(PROPERTY(minAltitude), minAltitude);
    this->setViewProperty(PROPERTY(maxAltitude), maxAltitude);
}

void VerticalProfilePresenter::clearMission()
{
    this->invokeViewMethod(PROPERTY(clearWaypoints));
}
