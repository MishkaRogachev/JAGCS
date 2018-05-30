#include "mission_list_presenter.h"

// Qt
#include <QSortFilterProxyModel>
#include <QVariant>
#include <QDebug>

// Internal
#include "mission.h"

#include "service_registry.h"
#include "mission_service.h"

#include "mission_list_model.h"

using namespace presentation;

class MissionListPresenter::Impl
{
public:
    domain::MissionService* const service = serviceRegistry->missionService();

    MissionListModel missionsModel;
    QSortFilterProxyModel sortModel;
};

MissionListPresenter::MissionListPresenter(QObject* parent):
    BasePresenter(parent),
    d(new Impl())
{
    d->sortModel.setSourceModel(&d->missionsModel);
    d->sortModel.setFilterRole(MissionListModel::MissionNameRole);
    d->sortModel.setSortRole(MissionListModel::MissionNameRole);
    d->sortModel.setDynamicSortFilter(true);
    d->sortModel.sort(0, Qt::AscendingOrder);

    d->missionsModel.setMissions(d->service->missions());

    connect(d->service, &domain::MissionService::missionAdded,
            &d->missionsModel, &MissionListModel::addMission);
    connect(d->service, &domain::MissionService::missionRemoved,
            &d->missionsModel, &MissionListModel::removeMission);
    connect(d->service, &domain::MissionService::missionChanged,
            &d->missionsModel, &MissionListModel::updateMission);
}

MissionListPresenter::~MissionListPresenter()
{}

void MissionListPresenter::addMission(const QGeoCoordinate& coordinate)
{
    d->service->addNewMission(tr("New Mission"), coordinate);
}

void MissionListPresenter::filter(const QString& filterString)
{
    d->sortModel.setFilterFixedString(filterString);
}

void MissionListPresenter::connectView(QObject* view)
{
    view->setProperty(PROPERTY(missions), QVariant::fromValue(&d->sortModel));
}
