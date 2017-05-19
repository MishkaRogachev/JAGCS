#include "mission_item_presenter.h"

// Qt
#include <QMap>
#include <QVariant>
#include <QDebug>

// Internal
#include "db_facade.h"
#include "mission.h"
#include "mission_item.h"

using namespace presentation;

class MissionItemPresenter::Impl
{
public:
    db::MissionPtr selectedMission;
    db::MissionItemPtr item;

    db::DbFacade* dbFacade;

    const QMap<db::MissionItem::Command, QString> commands = {
        { db::MissionItem::UnknownCommand, tr("None") },
        { db::MissionItem::Takeoff, tr("Takeoff") },
        { db::MissionItem::Waypoint, tr("Waypoint") },
        { db::MissionItem::LoiterAltitude, tr("LoiterAltitude") },
        { db::MissionItem::LoiterTurns, tr("LoiterTurns") },
        { db::MissionItem::Continue, tr("Continue") },
        { db::MissionItem::Return, tr("Return") },
        { db::MissionItem::Landing, tr("Landing") } };
};

MissionItemPresenter::MissionItemPresenter(db::DbFacade* dbFacade, QObject* object):
    BasePresenter(object),
    d(new Impl())
{
    d->dbFacade = dbFacade;

    connect(dbFacade, &db::DbFacade::missionItemAdded,
            this, &MissionItemPresenter::updateCount);
    connect(dbFacade, &db::DbFacade::missionItemRemoved,
            this, &MissionItemPresenter::updateCount);
}

MissionItemPresenter::~MissionItemPresenter()
{
    if (d->selectedMission)
    {
        d->dbFacade->saveMissionItems(d->selectedMission->id());
    }
}

db::MissionPtr MissionItemPresenter::selectedMission() const
{
    return d->selectedMission;
}

void MissionItemPresenter::setMission(const db::MissionPtr& mission)
{
    if (d->selectedMission == mission) return;

    if (d->selectedMission) // TODO: save only nessesory data
    {
        d->dbFacade->saveMissionItems(d->selectedMission->id());
    }

    d->selectedMission = mission;
    this->updateCount(true);
}

void MissionItemPresenter::setMissionItem(const db::MissionItemPtr& item)
{
    if (d->item == item) return;

    d->item = item;
    this->updateItem();
}

void MissionItemPresenter::connectView(QObject* view)
{
    connect(view, SIGNAL(addItem()), this, SLOT(onAddItem()));
    connect(view, SIGNAL(removeItem()), this, SLOT(onRemoveItem()));
    connect(view, SIGNAL(selectItem(int)), this, SLOT(onSelectItem(int)));

    connect(view, SIGNAL(setCommand(int)), this, SLOT(onSetCommand(int)));
    connect(view, SIGNAL(setAltitude(qreal)), this, SLOT(onSetAltitude(qreal)));
    connect(view, SIGNAL(setAltitudeRelative(bool)), this, SLOT(onSetAltitudeRelative(bool)));
    connect(view, SIGNAL(setLatitude(qreal)), this, SLOT(onSetLatitude(qreal)));
    connect(view, SIGNAL(setLongitude(qreal)), this, SLOT(onSetLongitude(qreal)));
    connect(view, SIGNAL(setRadius(qreal)), this, SLOT(onSetRadius(qreal)));
    connect(view, SIGNAL(setPeriods(int)), this, SLOT(onSetPeriods(int)));
    connect(view, SIGNAL(setPitch(qreal)), this, SLOT(onSetPitch(qreal)));

    QStringList commands = d->commands.values();
    this->setViewProperty(PROPERTY(commands), QVariant::fromValue(commands));

    this->updateCount(true);
}

void MissionItemPresenter::updateCount(bool gotoNewItem)
{
    if (d->selectedMission)
    {
        this->setViewProperty(PROPERTY(count), d->selectedMission->count());
        if (gotoNewItem) this->onSelectItem(d->selectedMission->count());
    }
    else
    {
        this->setViewProperty(PROPERTY(count), 0);
        d->item.clear();
        this->updateItem();
    }
}

void MissionItemPresenter::updateItem()
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
}

void MissionItemPresenter::onAddItem()
{
    if (d->selectedMission.isNull()) return;

    d->dbFacade->addNewMissionItem(d->selectedMission->id());
    int count = d->selectedMission->count();
    this->onSelectItem(count);
    this->setViewProperty(PROPERTY(picking), count > 1);
}

void MissionItemPresenter::onRemoveItem()
{
    if (d->item.isNull()) return;

    d->dbFacade->remove(d->item);
}

void MissionItemPresenter::onSelectItem(int index)
{
    if (d->selectedMission.isNull()) return;

    d->item = d->dbFacade->missionItem(d->selectedMission->id(), index);
    this->updateItem();
}

void MissionItemPresenter::onSetCommand(int command)
{
    if (d->item.isNull()) return;

    d->item->setCommand(db::MissionItem::Command(command));
    this->updateItem();
    emit d->dbFacade->missionItemChanged(d->item);
}

void MissionItemPresenter::onSetAltitude(qreal altitude)
{
    if (d->item.isNull()) return;

    d->item->setAltitude(altitude);
    emit d->dbFacade->missionItemChanged(d->item);
}

void MissionItemPresenter::onSetAltitudeRelative(bool relative)
{
    if (d->item.isNull()) return;

    d->item->setAltitudeRelative(relative);
    emit d->dbFacade->missionItemChanged(d->item);
}

void MissionItemPresenter::onSetLatitude(qreal latitude)
{
    if (d->item.isNull()) return;

    d->item->setLatitude(latitude);
    emit d->dbFacade->missionItemChanged(d->item);
}

void MissionItemPresenter::onSetLongitude(qreal longitude)
{
    if (d->item.isNull()) return;

    d->item->setLongitude(longitude);
    emit d->dbFacade->missionItemChanged(d->item);
}

void MissionItemPresenter::onSetRadius(qreal radius)
{
    if (d->item.isNull()) return;

    d->item->setRadius(radius);
    emit d->dbFacade->missionItemChanged(d->item);
}

void MissionItemPresenter::onSetPeriods(int periods)
{
    if (d->item.isNull()) return;

    d->item->setPeriods(periods);
    emit d->dbFacade->missionItemChanged(d->item);
}

void MissionItemPresenter::onSetPitch(qreal pitch)
{
    if (d->item.isNull()) return;

    d->item->setPitch(pitch);
    emit d->dbFacade->missionItemChanged(d->item);
}
