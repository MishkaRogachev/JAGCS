#include "mission_item_presenter.h"

// Qt
#include <QMap>
#include <QVariant>
#include <QCoreApplication>
#include <QDebug>

// Internal
#include "db_facade.h"
#include "mission.h"
#include "mission_item.h"

using namespace presentation;

namespace
{
    const QMap<db::MissionItem::Command, QString> commands =
    {
        { db::MissionItem::UnknownCommand, qApp->translate("MissionItemPresenter", "None") },
        { db::MissionItem::Takeoff, qApp->translate("MissionItemPresenter", "Takeoff") },
        { db::MissionItem::Waypoint, qApp->translate("MissionItemPresenter", "Waypoint") },
        { db::MissionItem::LoiterAltitude, qApp->translate("MissionItemPresenter", "LoiterAltitude") },
        { db::MissionItem::LoiterTurns, qApp->translate("MissionItemPresenter", "LoiterTurns") },
        { db::MissionItem::Continue, qApp->translate("MissionItemPresenter", "Continue") },
        { db::MissionItem::Return, qApp->translate("MissionItemPresenter", "Return") },
        { db::MissionItem::Landing, qApp->translate("MissionItemPresenter", "Landing") }
    };
}

class MissionItemPresenter::Impl
{
public:
    db::MissionPtr selectedMission;
    db::MissionItemPtr item;

    db::DbFacade* facade;
};

MissionItemPresenter::MissionItemPresenter(db::DbFacade* dbFacade, QObject* object):
    BasePresenter(object),
    d(new Impl())
{
    d->facade = dbFacade;

    connect(dbFacade, &db::DbFacade::missionItemAdded, this, &MissionItemPresenter::updateCount);
    connect(dbFacade, &db::DbFacade::missionItemRemoved, this, &MissionItemPresenter::updateCount);
}

MissionItemPresenter::~MissionItemPresenter()
{
    if (d->selectedMission)
    {
        d->facade->saveMissionItems(d->selectedMission->id());
    }
}

db::MissionPtr MissionItemPresenter::selectedMission() const
{
    return d->selectedMission;
}

void MissionItemPresenter::setMission(const db::MissionPtr& mission)
{
    if (d->selectedMission == mission) return;

    d->selectedMission = mission;
    this->updateCount(true);
}

void MissionItemPresenter::setMissionItem(const db::MissionItemPtr& item)
{
    if (d->item == item) return;

    d->item = item;
    this->updateView();
}

void MissionItemPresenter::remove()
{
    if (d->item.isNull()) return;

    d->facade->remove(d->item);
}

void MissionItemPresenter::selectItem(int index)
{
    if (d->selectedMission.isNull()) return;

    d->item = d->facade->missionItem(d->selectedMission->id(), index);
    this->updateView();
}

void MissionItemPresenter::save()
{
    d->item->setCommand(static_cast<db::MissionItem::Command>(
                            this->viewProperty(PROPERTY(command)).toInt()));
    d->item->setAltitude(this->viewProperty(PROPERTY(altitude)).toFloat());
    d->item->setAltitudeRelative(this->viewProperty(PROPERTY(relative)).toBool());
    d->item->setLatitude(this->viewProperty(PROPERTY(latitude)).toDouble());
    d->item->setLongitude(this->viewProperty(PROPERTY(longitude)).toDouble());
    d->item->setRadius(this->viewProperty(PROPERTY(radius)).toFloat());
    d->item->setPeriods(this->viewProperty(PROPERTY(periods)).toInt());
    d->item->setPitch(this->viewProperty(PROPERTY(pitch)).toFloat());

    if (!d->facade->save(d->item)) return;

    this->setViewProperty(PROPERTY(changed), false);
}

void MissionItemPresenter::updateView()
{
    if (d->item)
    {
        this->setViewProperty(PROPERTY(sequence), d->item->sequence());
        this->setViewProperty(PROPERTY(command), d->item->command());
        this->setViewProperty(PROPERTY(altitude), d->item->altitude());
        this->setViewProperty(PROPERTY(isAltitudeRelative), d->item->isAltitudeRelative());
        this->setViewProperty(PROPERTY(latitude), d->item->latitude());
        this->setViewProperty(PROPERTY(longitude), d->item->longitude());
        this->setViewProperty(PROPERTY(radius), d->item->radius());
        this->setViewProperty(PROPERTY(pitch), d->item->pitch());
        this->setViewProperty(PROPERTY(periods), d->item->periods());
    }
    else
    {
        this->setViewProperty(PROPERTY(sequence), 0);
        this->setViewProperty(PROPERTY(command), db::MissionItem::UnknownCommand);
    }

    this->setViewProperty(PROPERTY(changed), false);
}

void MissionItemPresenter::connectView(QObject* view)
{
    QStringList commands = ::commands.values();
    this->setViewProperty(PROPERTY(commands), QVariant::fromValue(commands));

    connect(view, SIGNAL(selectItem(int)), this, SLOT(selectItem(int)));

    connect(view, SIGNAL(save()), this, SLOT(save()));
    connect(view, SIGNAL(restore()), this, SLOT(updateView()));
    connect(view, SIGNAL(remove()), this, SLOT(remove()));

    this->updateCount(true);
}

void MissionItemPresenter::updateCount(bool gotoNewItem)
{
    if (d->selectedMission)
    {
        this->setViewProperty(PROPERTY(count), d->selectedMission->count());
        if (gotoNewItem) this->selectItem(d->selectedMission->count());
    }
    else
    {
        this->setViewProperty(PROPERTY(count), 0);
        d->item.clear();
        this->updateView();
    }
}
