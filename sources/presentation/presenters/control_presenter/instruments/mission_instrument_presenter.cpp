#include "mission_instrument_presenter.h"

// Qt
#include <QVariant>
#include <QDebug>

// Internal
#include "service_registry.h"
#include "mission_service.h"

#include "mission_item.h"
#include "mission_assignment.h"

#include "mission_items_status_presenter.h"

using namespace presentation;

class MissionInstrumentPresenter::Impl
{
public:
    domain::MissionService* service;

    dao::MissionAssignmentPtr assignment;

    MissionItemsStatusPresenter* itemsStatus;
};

MissionInstrumentPresenter::MissionInstrumentPresenter(int vehicleId, QObject* parent):
    BaseInstrumentPresenter(parent),
    d(new Impl())
{
    d->service = domain::ServiceRegistry::missionService();
    d->assignment = d->service->vehicleAssignment(vehicleId);

    d->itemsStatus = new MissionItemsStatusPresenter(this);
    connect(d->itemsStatus, &MissionItemsStatusPresenter::selectItem,
            this, &MissionInstrumentPresenter::onSelectItem);

    if (d->assignment)
    {
        d->itemsStatus->selectMission(d->service->mission(d->assignment->missionId()));
        connect(d->itemsStatus, &MissionItemsStatusPresenter::selectItem,
                this, [this](int sequence) {
            d->itemsStatus->selectMissionItem(
                        d->service->missionItem(d->assignment->missionId(), sequence));
        });
    }

    connect(d->service, &domain::MissionService::assignmentChanged,
            this, [this](const dao::MissionAssignmentPtr& assignment) {
        if (d->assignment.isNull() || d->assignment != assignment) return;

        this->setViewsProperty(PROPERTY(downloading), bool(d->assignment->status() ==
                               dao::MissionAssignment::Downloading));
    });
}

MissionInstrumentPresenter::~MissionInstrumentPresenter()
{}

void MissionInstrumentPresenter::onDownloadMission()
{
    if (d->assignment) d->service->download(d->assignment);
}

void MissionInstrumentPresenter::onCancelSyncMission()
{
    if (d->assignment) d->service->cancelSync(d->assignment);
}

void MissionInstrumentPresenter::selectMissionItem(const dao::MissionItemPtr& item)
{
    if (item && item->missionId() == d->assignment->missionId())
    {
        d->itemsStatus->selectMissionItem(item);
    }
    else
    {
        d->itemsStatus->selectMissionItem(dao::MissionItemPtr());
    }

    emit missionItemSelected(d->itemsStatus->missionItem());
}

void MissionInstrumentPresenter::connectView(QObject* view)
{
    QObject* statusView = view->findChild<QObject*>(NAME(itemsStatus));
    if (statusView) d->itemsStatus->setView(statusView);

    connect(view, SIGNAL(downloadMission()), this, SLOT(onDownloadMission()));
    connect(view, SIGNAL(cancelSyncMission()), this, SLOT(onCancelSyncMission()));
}

void MissionInstrumentPresenter::onSelectItem(int item)
{
    if (d->assignment.isNull()) return;

    emit missionItemSelected(d->service->missionItem(d->assignment->missionId(), item));
}
