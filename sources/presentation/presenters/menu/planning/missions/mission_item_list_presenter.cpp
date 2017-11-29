#include "mission_item_list_presenter.h"

// Qt
#include <QVariant>
#include <QDebug>

// Internal
#include "mission.h"
#include "mission_item.h"

#include "service_registry.h"
#include "mission_service.h"

using namespace presentation;

MissionItemListPresenter::MissionItemListPresenter(QObject* parent):
    BasePresenter(parent),
    m_service(domain::ServiceRegistry::missionService()),
    m_missionId(0)
{
    connect(m_service, &domain::MissionService::missionItemAdded, this,
            [this](dao::MissionItemPtr item) {
        if (item->missionId() == m_missionId) this->updateMissionItems();
    });
    connect(m_service, &domain::MissionService::missionItemRemoved, this,
            [this](dao::MissionItemPtr item) {
        if (item->missionId() == m_missionId) this->updateMissionItems();
    });
}

void MissionItemListPresenter::setMission(int id)
{
    m_missionId = id;

    this->updateMissionItems(true);
}

void MissionItemListPresenter::updateMissionItems(bool selectLast)
{
    QVariantList itemIds;
    int selectedItemId = 0;

    for (const dao::MissionItemPtr& item: m_service->missionItems(m_missionId))
    {
        itemIds.append(selectedItemId = item->id());
    }

    this->setViewProperty(PROPERTY(itemIds), itemIds);
    if (selectLast) this->setViewProperty(PROPERTY(selectedItemId), selectedItemId);
}
