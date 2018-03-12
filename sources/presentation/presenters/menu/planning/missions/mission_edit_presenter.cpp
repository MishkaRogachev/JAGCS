#include "mission_edit_presenter.h"

// Qt
#include <QMap>
#include <QVariant>
#include <QDebug>

// Internal
#include "service_registry.h"
#include "mission_service.h"

#include "mission.h"
#include "mission_item.h"

using namespace presentation;

class MissionEditPresenter::Impl
{
public:
    domain::MissionService* const service = serviceRegistry->missionService();

    dto::MissionPtr mission;
    dto::MissionItemPtr item;
};

MissionEditPresenter::MissionEditPresenter(QObject* object):
    BasePresenter(object),
    d(new Impl())
{
    connect(d->service, &domain::MissionService::missionChanged, this,
            [this](const dto::MissionPtr& mission) {
        if (mission == d->mission) this->updateCount();
    });
}

MissionEditPresenter::~MissionEditPresenter()
{}

void MissionEditPresenter::setMission(int id)
{
    d->mission = d->service->mission(id);

    this->updateCount();
}

void MissionEditPresenter::setItem(int id)
{
    d->item = d->service->missionItem(id);

    this->updateItem();
}

void MissionEditPresenter::selectItem(int sequence)
{
    if (d->mission.isNull()) return;

    d->item = d->service->missionItem(d->mission->id(), sequence);

    this->updateItem();
}

void MissionEditPresenter::updateCount()
{
    this->setViewProperty(PROPERTY(count), d->mission ? d->mission->count() : 0);
}

void MissionEditPresenter::updateItem()
{
    this->setViewProperty(PROPERTY(selectedItemId), d->item ? d->item->id() : 0);
    this->setViewProperty(PROPERTY(sequence), d->item ? d->item->sequence() : -1);
}

void MissionEditPresenter::remove()
{
    if (d->item.isNull()) return;

    int sequence = d->item->sequence();
    d->service->remove(d->item);

    this->selectItem(sequence - 1);
}

void MissionEditPresenter::addItem(dto::MissionItem::Command command)
{
    if (d->mission.isNull()) return;

    d->item = d->service->addNewMissionItem(d->mission->id(), command,
                                            d->item ? d->item->sequence() + 1 : 0);

    this->updateItem();
    if (d->item && d->item->isPositionatedItem()) this->setViewProperty(PROPERTY(picking), true);
}

void MissionEditPresenter::changeSequence(int sequence)
{
    if (d->item.isNull()) return;

    dto::MissionItemPtr other = d->service->missionItem(d->mission->id(), sequence);
    if (other.isNull()) return;

    d->service->swapItems(d->item, other);
    this->selectItem(sequence);
}

