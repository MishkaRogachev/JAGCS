#include "mission_instrument_presenter.h"

// Qt
#include <QVariant>
#include <QDebug>

// Internal
#include "service_registry.h"
#include "mission_service.h"
#include "command_service.h"

#include "mission_item.h"
#include "mission_assignment.h"

#include "mission_items_status_presenter.h"

using namespace presentation;

class MissionInstrumentPresenter::Impl
{
public:
    domain::MissionService* missionService = domain::ServiceRegistry::missionService();
    domain::CommandService* commandService = domain::ServiceRegistry::commandService();

    dao::MissionAssignmentPtr assignment;

    MissionItemsStatusPresenter* itemsStatus;
};

MissionInstrumentPresenter::MissionInstrumentPresenter(int vehicleId, QObject* parent):
    BaseInstrumentPresenter(parent),
    d(new Impl())
{
    d->assignment = d->missionService->vehicleAssignment(vehicleId);

    d->itemsStatus = new MissionItemsStatusPresenter(this);
    connect(d->itemsStatus, &MissionItemsStatusPresenter::selectItem,
            this, &MissionInstrumentPresenter::onSelectItem);

    if (d->assignment)
    {
        d->itemsStatus->selectMission(d->missionService->mission(d->assignment->missionId()));
        connect(d->itemsStatus, &MissionItemsStatusPresenter::selectItem,
                this, [this](int sequence) {
            d->itemsStatus->selectMissionItem(
                        d->missionService->missionItem(d->assignment->missionId(), sequence));
        });
    }

    connect(d->missionService, &domain::MissionService::assignmentChanged,
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
    if (d->assignment) d->missionService->download(d->assignment);
}

void MissionInstrumentPresenter::onCancelSyncMission()
{
    if (d->assignment) d->missionService->cancelSync(d->assignment);
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

    connect(this, SIGNAL(activateItem()), view, SLOT());
}

void MissionInstrumentPresenter::onSelectItem(int item)
{
    if (d->assignment.isNull()) return;

    emit missionItemSelected(d->missionService->missionItem(d->assignment->missionId(), item));
}

void MissionInstrumentPresenter::activateItem()
{
    if (d->assignment.isNull() || d->itemsStatus->missionItem().isNull()) return;

    domain::Command command(domain::Command::SetCurrentItem, d->assignment->vehicleId());
    command.addArgument(d->itemsStatus->missionItem()->sequence());
    d->commandService->executeCommand(command);
}
