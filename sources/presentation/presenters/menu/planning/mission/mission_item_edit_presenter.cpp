#include "mission_item_edit_presenter.h"

// Qt
#include <QMap>
#include <QVariant>
#include <QDebug>

// Internal
#include "service_registry.h"
#include "mission_service.h"

#include "mission.h"
#include "mission_item.h"

#include "translation_helper.h"

using namespace presentation;

class MissionItemEditPresenter::Impl
{
public:
    domain::MissionService* service = domain::ServiceRegistry::missionService();

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

MissionItemEditPresenter::MissionItemEditPresenter(QObject* object):
    BasePresenter(object),
    d(new Impl())
{
    connect(d->service, &domain::MissionService::missionItemAdded, this, &MissionItemEditPresenter::updateCount);
    connect(d->service, &domain::MissionService::missionItemRemoved, this, &MissionItemEditPresenter::updateCount);
    connect(d->service, &domain::MissionService::missionItemChanged,
            this, [this](dao::MissionItemPtr item) { if (item == d->item) this->updateView(); });
}

MissionItemEditPresenter::~MissionItemEditPresenter()
{}

dao::MissionPtr MissionItemEditPresenter::selectedMission() const
{
    return d->mission;
}

void MissionItemEditPresenter::selectMission(const dao::MissionPtr& mission)
{
    if (d->mission == mission) return;

    emit itemSelected(dao::MissionItemPtr());

    d->mission = mission;
    this->updateCount();
}

void MissionItemEditPresenter::enablePicker()
{
    if (d->item.isNull() || !d->item->isPositionatedItem() || d->item->isCurrent()) return;

    this->setViewProperty(PROPERTY(picking), true);
}

void MissionItemEditPresenter::remove()
{
    if (d->item.isNull()) return;

    d->service->remove(d->item);
}

void MissionItemEditPresenter::selectItem(int index)
{
    if (d->mission.isNull()) return;

    dao::MissionItemPtr item = d->service->missionItem(d->mission->id(), index);
    if (d->item == item) return;

    d->item = item;
    this->updateAvailableCommands();
    this->updateView();

    emit itemSelected(item);
}

void MissionItemEditPresenter::save()
{
    int commandIndex = this->viewProperty(PROPERTY(commandIndex)).toInt();
    if (commandIndex < d->availableCommands.count())
    {
        d->item->setCommand(d->availableCommands.at(commandIndex));
    }
    d->item->setAltitudeRelative(this->viewProperty(PROPERTY(altitudeRelative)).toBool());
    d->item->setCoordinate(this->viewProperty(PROPERTY(position)).value<QGeoCoordinate>());
    d->item->setAltitude(this->viewProperty(PROPERTY(altitude)).toFloat());

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

void MissionItemEditPresenter::updateView()
{
    if (d->mission && d->item)
    {
        int homeAltitude = 0;
        dao::MissionItemPtr home = d->service->missionItem(d->mission->id(), 0);

        if (home)
        {
            homeAltitude = home->altitude();
        }
        this->setViewProperty(PROPERTY(homeAltitude), homeAltitude);

        int previousGlobalAltitude = 0;
        bool updateAltitude = d->item->isAltitudedItem();

        QGeoCoordinate previousPosition;
        bool updatePosition = d->item->isPositionatedItem();

        for (int seq = d->item->sequence() - 1; seq >= 0; --seq)
        {
            dao::MissionItemPtr previous = d->service->missionItem(d->mission->id(), seq);
            if (!previous) continue;

            if (updateAltitude && previous->isAltitudedItem())
            {
                previousGlobalAltitude = previous->isAltitudeRelative() ?
                                              previous->altitude() + homeAltitude :
                                              previous->altitude();
                updateAltitude = false;
            }

            if (previous->isPositionatedItem())
            {
                previousPosition = previous->coordinate();
                updatePosition = false;
            }
            if (!updateAltitude && !updatePosition) break;
        }
        this->setViewProperty(PROPERTY(previousGlobalAltitude), previousGlobalAltitude);
        this->setViewProperty(PROPERTY(previousPosition), QVariant::fromValue(previousPosition));

        this->setViewProperty(PROPERTY(editEnabled), !d->item->isCurrent() ||
                              d->item->sequence() == 0);
        this->setViewProperty(PROPERTY(sequence), d->item->sequence());
        this->setViewProperty(PROPERTY(command), d->item->command());
        this->setViewProperty(PROPERTY(commandIndex), d->availableCommands.indexOf(d->item->command()));
        this->setViewProperty(PROPERTY(altitudeRelative), d->item->isAltitudeRelative());
        this->setViewProperty(PROPERTY(savedPosition), QVariant::fromValue(d->item->coordinate()));
        this->setViewProperty(PROPERTY(position), QVariant::fromValue(d->item->coordinate()));
        this->setViewProperty(PROPERTY(altitude), d->item->altitude());
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

void MissionItemEditPresenter::connectView(QObject* view)
{
    this->updateAvailableCommands();

    connect(view, SIGNAL(changeSequence(int)), this, SLOT(onChangeSequence(int)));
    connect(view, SIGNAL(updateCommand(int)), this, SLOT(onUpdateCommand(int)));

    connect(view, SIGNAL(save()), this, SLOT(save()));
    connect(view, SIGNAL(restore()), this, SLOT(updateView()));
    connect(view, SIGNAL(remove()), this, SLOT(remove()));

    this->updateCount();
}

void MissionItemEditPresenter::updateCount()
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

void MissionItemEditPresenter::updateAvailableCommands()
{
    d->updateAvailableCommands();

    QStringList commands;
    for (dao::MissionItem::Command command: d->availableCommands)
    {
        commands.append(d->helper.translateCommand(command));
    }
    this->setViewProperty(PROPERTY(commands), QVariant::fromValue(commands));
}

void MissionItemEditPresenter::onUpdateCommand(int commandIndex)
{
    if (commandIndex > 0 && commandIndex < d->availableCommands.count())
    {
        this->setViewProperty(PROPERTY(command), d->availableCommands.at(commandIndex));
    }
}

void MissionItemEditPresenter::onChangeSequence(int sequence)
{
    if (d->item.isNull()) return;

    dao::MissionItemPtr other = d->service->missionItem(d->mission->id(), sequence);
    if (other.isNull()) return;

    d->service->swapItems(d->item, other);

    emit itemSelected(d->item);
}
