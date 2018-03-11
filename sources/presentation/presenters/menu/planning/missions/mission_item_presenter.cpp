#include "mission_item_presenter.h"

// Qt
#include <QVariant>
#include <QDebug>

// Internal
#include "mission_item.h"

#include "service_registry.h"
#include "mission_service.h"

using namespace presentation;

MissionItemPresenter::MissionItemPresenter(QObject* parent):
    BasePresenter(parent),
    m_service(domain::ServiceRegistry::missionService())
{
    connect(m_service, &domain::MissionService::missionItemChanged, this,
            [this](const dto::MissionItemPtr& item) {
        if (m_item && m_item == item) this->updateItem();
    });
}

void MissionItemPresenter::setItem(int id)
{
    m_item = m_service->missionItem(id);

    this->updateItem();
}

void MissionItemPresenter::updateItem()
{
    this->setViewProperty(PROPERTY(current), m_item ? m_item->isCurrent() : false);
    this->setViewProperty(PROPERTY(reached), m_item ? m_item->isReached() : false);
    this->setViewProperty(PROPERTY(sequence), m_item ? m_item->sequence() : -1);
    this->setViewProperty(PROPERTY(status), m_item ? m_item->status() : false);
    this->setViewProperty(PROPERTY(command), m_item ? m_item->command() : false);
}
