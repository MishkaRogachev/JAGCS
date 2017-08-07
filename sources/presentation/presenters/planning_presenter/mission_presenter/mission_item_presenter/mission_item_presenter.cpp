#include "mission_item_presenter.h"

// Qt
#include <QMap>
#include <QVariant>
#include <QCoreApplication>
#include <QDebug>

// Internal
#include "mission_service.h"
#include "mission.h"
#include "mission_item.h"

using namespace presentation;

namespace
{
    const QMap<dao::MissionItem::Command, QString> commands =
    {
        { dao::MissionItem::UnknownCommand, qApp->translate("MissionItemPresenter", "None") },
        { dao::MissionItem::Home, qApp->translate("MissionItemPresenter", "Home") },
        { dao::MissionItem::Takeoff, qApp->translate("MissionItemPresenter", "Takeoff") },
        { dao::MissionItem::Waypoint, qApp->translate("MissionItemPresenter", "Waypoint") },
        { dao::MissionItem::LoiterUnlim, qApp->translate("MissionItemPresenter", "Loiter unlim") },
        { dao::MissionItem::LoiterAltitude, qApp->translate("MissionItemPresenter", "Loiter altitude") },
        { dao::MissionItem::LoiterTurns, qApp->translate("MissionItemPresenter", "Loiter turns") },
        { dao::MissionItem::LoiterTime, qApp->translate("MissionItemPresenter", "Loiter time") },
        { dao::MissionItem::Continue, qApp->translate("MissionItemPresenter", "Continue") },
        { dao::MissionItem::Return, qApp->translate("MissionItemPresenter", "Return") },
        { dao::MissionItem::Landing, qApp->translate("MissionItemPresenter", "Landing") }
    };
}

class MissionItemPresenter::Impl
{
public:
    dao::MissionPtr selectedMission;
    dao::MissionItemPtr item;

    domain::MissionService* service;
};

MissionItemPresenter::MissionItemPresenter(domain::MissionService* service, QObject* object):
    BasePresenter(object),
    d(new Impl())
{
    d->service = service;

    connect(service, &domain::MissionService::missionItemAdded, this, &MissionItemPresenter::updateCount);
    connect(service, &domain::MissionService::missionItemRemoved, this, &MissionItemPresenter::updateCount);
    connect(service, &domain::MissionService::missionItemChanged,
            this, [this](dao::MissionItemPtr item) { if (item == d->item) this->updateView(); });
}

MissionItemPresenter::~MissionItemPresenter()
{
    if (d->selectedMission)
    {
        d->service->saveMissionItems(d->selectedMission->id());
    }
}

dao::MissionPtr MissionItemPresenter::selectedMission() const
{
    return d->selectedMission;
}

void MissionItemPresenter::setMission(const dao::MissionPtr& mission)
{
    if (d->selectedMission == mission) return;

    emit itemSelected(dao::MissionItemPtr());

    d->selectedMission = mission;
    this->updateCount();
}

void MissionItemPresenter::setPicking(bool picking)
{
    this->setViewProperty(PROPERTY(picking), true);
}

void MissionItemPresenter::remove()
{
    if (d->item.isNull()) return;

    d->service->remove(d->item);
}

void MissionItemPresenter::selectItem(int index)
{
    if (d->selectedMission.isNull()) return;

    dao::MissionItemPtr item = d->service->missionItem(d->selectedMission->id(), index);
    if (d->item == item) return;

    d->item = item;
    this->updateView();

    emit itemSelected(item);
}

void MissionItemPresenter::save()
{
    d->item->setCommand(static_cast<dao::MissionItem::Command>(
                            this->viewProperty(PROPERTY(command)).toInt()));
    d->item->setAltitude(this->viewProperty(PROPERTY(altitude)).toFloat());
    d->item->setAltitudeRelative(this->viewProperty(PROPERTY(isAltitudeRelative)).toBool());
    d->item->setLatitude(this->viewProperty(PROPERTY(latitude)).toDouble());
    d->item->setLongitude(this->viewProperty(PROPERTY(longitude)).toDouble());
    // TODO: check parameter
    d->item->setParameter(dao::MissionItem::Radius, this->viewProperty(PROPERTY(radius)));
    d->item->setParameter(dao::MissionItem::Repeats, this->viewProperty(PROPERTY(repeats)));
    d->item->setParameter(dao::MissionItem::Time, this->viewProperty(PROPERTY(time)));
    d->item->setParameter(dao::MissionItem::Pitch, this->viewProperty(PROPERTY(pitch)));
    d->item->setParameter(dao::MissionItem::Yaw, this->viewProperty(PROPERTY(yaw)));
    d->item->setParameter(dao::MissionItem::Clockwise, this->viewProperty(PROPERTY(clockwise)));
    d->item->setStatus(dao::MissionItem::NotActual);

    if (!d->service->save(d->item)) return;
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
        // TODO: check parameter
        this->setViewProperty(PROPERTY(radius), d->item->parameter(dao::MissionItem::Radius));
        this->setViewProperty(PROPERTY(repeats), d->item->parameter(dao::MissionItem::Repeats));
        this->setViewProperty(PROPERTY(time), d->item->parameter(dao::MissionItem::Time));
        this->setViewProperty(PROPERTY(pitch), d->item->parameter(dao::MissionItem::Pitch));
        this->setViewProperty(PROPERTY(yaw), d->item->parameter(dao::MissionItem::Yaw));
        this->setViewProperty(PROPERTY(clockwise), d->item->parameter(dao::MissionItem::Clockwise));
    }
    else
    {
        this->setViewProperty(PROPERTY(sequence), -1);
        this->setViewProperty(PROPERTY(command), dao::MissionItem::UnknownCommand);
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

    this->updateCount();
}

void MissionItemPresenter::updateCount()
{
    if (d->selectedMission)
    {
        this->setViewProperty(PROPERTY(count), d->selectedMission->count());
        this->selectItem(d->selectedMission->count() - 1);
    }
    else
    {
        this->setViewProperty(PROPERTY(count), 0);
        d->item.clear();
        this->updateView();
    }
}
