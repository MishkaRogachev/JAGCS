#include "mission_map_presenter.h"

// Qt
#include <QDebug>

// Internal
#include "mission_service.h"
#include "mission.h"

#include "mission_map_item_model.h"

using namespace presentation;

class MissionMapPresenter::Impl
{
public:
    domain::MissionService* missionService;

    MissionMapItemModel missionModel;

    Impl(domain::MissionService* missionService):
        missionService(missionService),
        missionModel(missionService)
    {}
};

MissionMapPresenter::MissionMapPresenter(domain::MissionService* missionService,
                                         QObject* parent):
    MapPresenter(parent),
    d(new Impl(missionService))
{}

MissionMapPresenter::~MissionMapPresenter()
{
    delete d;
}

void MissionMapPresenter::connectView(QObject* view)
{
    MapPresenter::connectView(view);

    this->setViewProperty(PROPERTY(missionModel),
                          QVariant::fromValue(&d->missionModel));
}
