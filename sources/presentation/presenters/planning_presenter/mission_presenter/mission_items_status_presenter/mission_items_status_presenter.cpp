#include "mission_items_status_presenter.h"

// Qt
#include <QVariant>
#include <QDebug>

// Internal
#include "service_registry.h"
#include "mission_service.h"

#include "mission.h"
#include "mission_item.h"

using namespace presentation;

class MissionItemsStatusPresenter::Impl
{
public:
    domain::MissionService* service = domain::ServiceRegistry::missionService();

    dao::MissionPtr mission;
    dao::MissionItemPtr item;
};

MissionItemsStatusPresenter::MissionItemsStatusPresenter(QObject* object):
    BasePresenter(object),
    d(new Impl())
{
    connect(d->service, &domain::MissionService::missionItemAdded,
            this, &MissionItemsStatusPresenter::updateItemsStatus);
    connect(d->service, &domain::MissionService::missionItemRemoved,
            this, &MissionItemsStatusPresenter::updateItemsStatus);
    connect(d->service, &domain::MissionService::missionItemChanged,
            this, &MissionItemsStatusPresenter::updateItemsStatus);
}

MissionItemsStatusPresenter::~MissionItemsStatusPresenter()
{}

void MissionItemsStatusPresenter::selectMission(const dao::MissionPtr& mission)
{
    d->mission = mission;

    this->updateItemsStatus();
}

void MissionItemsStatusPresenter::selectMissionItem(const dao::MissionItemPtr& item)
{
    d->item = item;

    this->updateSelectedItem();
}

void MissionItemsStatusPresenter::connectView(QObject* view)
{
    connect(view, SIGNAL(selectItem(int)), this, SIGNAL(selectItem(int)));

    this->updateItemsStatus();
}

void MissionItemsStatusPresenter::updateItemsStatus()
{
    QVariantList items;

    if (d->mission)
    {
        for (const dao::MissionItemPtr& item: d->service->missionItems(d->mission->id()))
        {
            items.append(QVariant::fromValue(*item.data()));
        }
    }

    this->setViewProperty(PROPERTY(items), items);
    this->updateSelectedItem();
}

void MissionItemsStatusPresenter::updateSelectedItem()
{
    this->setViewProperty(PROPERTY(selectedItem), d->item ? d->item->sequence() : -1);
}
