#include "mission_item_presenter.h"

// Qt
#include <QMap>
#include <QVariant>
#include <QDebug>

// Internal
#include "mission_service.h"
#include "mission.h"
#include "mission_item.h"

#include "translation_helper.h"

using namespace presentation;

class MissionItemPresenter::Impl
{
public:
    domain::MissionService* service;

    dao::MissionPtr mission;
    dao::MissionItemPtr item;

    TranslationHelper helper;

    QList<dao::MissionItem::Command> availableCommands;

    void updateAvailableCommands()
    {
        availableCommands.clear();

        if (item.isNull()) return;

        if (item->sequence() == 0)
        {
            availableCommands.append(dao::MissionItem::Home);
        }
        else
        {
            availableCommands.append(
            { dao::MissionItem::Takeoff, dao::MissionItem::Waypoint, dao::MissionItem::LoiterUnlim,
              dao::MissionItem::LoiterAltitude, dao::MissionItem::LoiterTurns, dao::MissionItem::LoiterTime,
              dao::MissionItem::Continue, dao::MissionItem::Return, dao::MissionItem::Landing,
              dao::MissionItem::SetSpeed });
        }
    }
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
{}

dao::MissionPtr MissionItemPresenter::selectedMission() const
{
    return d->mission;
}

void MissionItemPresenter::setMission(const dao::MissionPtr& mission)
{
    if (d->mission == mission) return;

    emit itemSelected(dao::MissionItemPtr());

    d->mission = mission;
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
    if (d->mission.isNull()) return;

    dao::MissionItemPtr item = d->service->missionItem(d->mission->id(), index);
    if (d->item == item) return;

    d->item = item;
    this->updateAvailableCommands();
    this->updateView();

    emit itemSelected(item);
}

void MissionItemPresenter::save()
{
    int commandIndex = this->viewProperty(PROPERTY(commandIndex)).toInt();
    if (commandIndex < d->availableCommands.count())
    {
        d->item->setCommand(d->availableCommands.at(commandIndex));
    }
    d->item->setAltitude(this->viewProperty(PROPERTY(altitude)).toFloat());
    d->item->setAltitudeRelative(this->viewProperty(PROPERTY(isAltitudeRelative)).toBool());
    d->item->setLatitude(this->viewProperty(PROPERTY(latitude)).toDouble());
    d->item->setLongitude(this->viewProperty(PROPERTY(longitude)).toDouble());

    d->item->setParameter(dao::MissionItem::AbortAltitude, this->viewProperty(PROPERTY(abortAltitude)));
    d->item->setParameter(dao::MissionItem::Radius, this->viewProperty(PROPERTY(radius)));
    d->item->setParameter(dao::MissionItem::Repeats, this->viewProperty(PROPERTY(repeats)));
    d->item->setParameter(dao::MissionItem::Time, this->viewProperty(PROPERTY(time)));
    d->item->setParameter(dao::MissionItem::Pitch, this->viewProperty(PROPERTY(pitch)));
    d->item->setParameter(dao::MissionItem::Yaw, this->viewProperty(PROPERTY(yaw)));
    d->item->setParameter(dao::MissionItem::Clockwise, this->viewProperty(PROPERTY(clockwise)));
    d->item->setParameter(dao::MissionItem::IsGroundSpeed, this->viewProperty(PROPERTY(isGroundSpeed)));
    d->item->setParameter(dao::MissionItem::Speed, this->viewProperty(PROPERTY(speedEnabled)).toBool() ?
                              this->viewProperty(PROPERTY(speed)) : QVariant());
    d->item->setParameter(dao::MissionItem::Throttle, this->viewProperty(PROPERTY(throttleEnabled)).toBool() ?
                              this->viewProperty(PROPERTY(throttle)) : QVariant());

    d->item->setStatus(dao::MissionItem::NotActual);

    if (!d->service->save(d->item)) return;
}

void MissionItemPresenter::updateView()
{
    if (d->item)
    {
        this->setViewProperty(PROPERTY(editEnabled), !d->service->isItemCurrent(d->item));
        this->setViewProperty(PROPERTY(sequence), d->item->sequence());
        this->setViewProperty(PROPERTY(command), d->item->command());
        this->setViewProperty(PROPERTY(commandIndex), d->availableCommands.indexOf(d->item->command()));
        this->setViewProperty(PROPERTY(altitude), d->item->altitude());
        this->setViewProperty(PROPERTY(isAltitudeRelative), d->item->isAltitudeRelative());
        this->setViewProperty(PROPERTY(climb), d->item->climb());
        this->setViewProperty(PROPERTY(latitude), d->item->latitude());
        this->setViewProperty(PROPERTY(longitude), d->item->longitude());
        this->setViewProperty(PROPERTY(distance), d->item->distance());
        this->setViewProperty(PROPERTY(azimuth), d->item->azimuth());
        this->setViewProperty(PROPERTY(abortAltitude), d->item->parameter(dao::MissionItem::AbortAltitude));
        this->setViewProperty(PROPERTY(radius), d->item->parameter(dao::MissionItem::Radius));
        this->setViewProperty(PROPERTY(repeats), d->item->parameter(dao::MissionItem::Repeats));
        this->setViewProperty(PROPERTY(time), d->item->parameter(dao::MissionItem::Time));
        this->setViewProperty(PROPERTY(pitch), d->item->parameter(dao::MissionItem::Pitch));
        this->setViewProperty(PROPERTY(yaw), d->item->parameter(dao::MissionItem::Yaw));
        this->setViewProperty(PROPERTY(clockwise), d->item->parameter(dao::MissionItem::Clockwise));
        this->setViewProperty(PROPERTY(isGroundSpeed), d->item->parameter(dao::MissionItem::IsGroundSpeed));
        this->setViewProperty(PROPERTY(speed), d->item->parameter(dao::MissionItem::Speed));
        this->setViewProperty(PROPERTY(speedEnabled), d->item->parameter(dao::MissionItem::Speed).isValid());
        this->setViewProperty(PROPERTY(throttle), d->item->parameter(dao::MissionItem::Throttle));
        this->setViewProperty(PROPERTY(throttleEnabled), d->item->parameter(dao::MissionItem::Throttle).isValid());
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
    this->updateAvailableCommands();

    connect(view, SIGNAL(selectItem(int)), this, SLOT(selectItem(int)));
    connect(view, SIGNAL(updateCommand(int)), this, SLOT(onUpdateCommand(int)));

    connect(view, SIGNAL(save()), this, SLOT(save()));
    connect(view, SIGNAL(restore()), this, SLOT(updateView()));
    connect(view, SIGNAL(remove()), this, SLOT(remove()));

    this->updateCount();
}

void MissionItemPresenter::updateCount()
{
    if (d->mission)
    {
        this->setViewProperty(PROPERTY(count), d->mission->count());
        this->selectItem(d->mission->count() - 1);
    }
    else
    {
        this->setViewProperty(PROPERTY(count), 0);
        d->item.clear();
        this->updateView();
    }
}

void MissionItemPresenter::updateAvailableCommands()
{
    d->updateAvailableCommands();

    QStringList commands;
    for (dao::MissionItem::Command command: d->availableCommands)
    {
        commands.append(d->helper.translateCommand(command));
    }
    this->setViewProperty(PROPERTY(commands), QVariant::fromValue(commands));
}

void MissionItemPresenter::onUpdateCommand(int commandIndex)
{
    if (commandIndex > 0 && commandIndex < d->availableCommands.count())
    {
        this->setViewProperty(PROPERTY(command), d->availableCommands.at(commandIndex));
    }
}
