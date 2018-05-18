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
    m_service(serviceRegistry->missionService()),
    m_missionId(0)
{
    connect(m_service, &domain::MissionService::missionItemAdded, this,
            [this](dto::MissionItemPtr item) {
        if (item->missionId() == m_missionId) this->updateMissionItems();
    });
    connect(m_service, &domain::MissionService::missionItemRemoved, this,
            [this](dto::MissionItemPtr item) {
        if (item->missionId() == m_missionId) this->updateMissionItems();
    });
    connect(m_service, &domain::MissionService::missionItemChanged, this,
            [this](dto::MissionItemPtr item) {
        if (item->missionId() == m_missionId) this->updateMissionItems();
    });
}

void MissionItemListPresenter::setMission(int id)
{
    if (m_missionId == id) return;

    m_missionId = id;
    this->updateMissionItems();
}

void MissionItemListPresenter::updateMissionItems()
{
    QVariantList itemIds;

    for (const dto::MissionItemPtr& item: m_service->missionItems(m_missionId))
    {
        itemIds.append(item->id());
    }
    this->setViewProperty(PROPERTY(itemIds), itemIds);
}
