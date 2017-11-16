#include "mission_list_presenter.h"

// Qt
#include <QVariant>
#include <QDebug>

// Internal
#include "settings_provider.h"

#include "mission.h"

#include "service_registry.h"
#include "mission_service.h"

using namespace presentation;

class MissionListPresenter::Impl
{
public:
    domain::MissionService* service = domain::ServiceRegistry::missionService();
};

MissionListPresenter::MissionListPresenter(QObject* parent):
    BasePresenter(parent),
    d(new Impl())
{}

MissionListPresenter::~MissionListPresenter()
{}

void MissionListPresenter::updateMissions()
{
    QVariantList missions;
    QVariantList visibilities;

    for (dao::MissionPtr& mission: d->service->missions())
    {
        missions.append(QVariant::fromValue(*mission));
        visibilities.append(settings::Provider::value(settings::mission::visibility +
                                                      "/" + mission->id()));
    }

    this->setViewProperty("model", missions);
    this->setViewProperty("visibilities", visibilities);
}

void MissionListPresenter::connectView(QObject* view)
{
    this->updateMissions();

    connect(view, SIGNAL(setVisible(int, bool)), this, SLOT(onSetVisible(int, bool)));
}

void MissionListPresenter::onSetVisible(int id, bool visible)
{
    settings::Provider::setValue(settings::mission::visibility + "/" + id, visible);
    d->service->missionChanged(d->service->mission(id));
}
