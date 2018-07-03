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
    domain::MissionService* const service = serviceRegistry->missionService();

    dto::MissionItemPtr item;

    TranslationHelper helper;

    QList<dto::MissionItem::Command> availableCommands;

    void updateAvailableCommands()
    {
        availableCommands.clear();

        if (item.isNull()) return;

        if (item->sequence() == 0)
        {
            availableCommands.append(dto::MissionItem::Home);
        }
        else
        {
            availableCommands.append(
            { dto::MissionItem::Takeoff, dto::MissionItem::Waypoint, dto::MissionItem::LoiterUnlim,
              dto::MissionItem::LoiterAltitude, dto::MissionItem::LoiterTurns, dto::MissionItem::LoiterTime,
              dto::MissionItem::Continue, dto::MissionItem::Return, dto::MissionItem::Landing,
              dto::MissionItem::SetSpeed });
        }
    }
};

MissionItemEditPresenter::MissionItemEditPresenter(QObject* object):
    BasePresenter(object),
    d(new Impl())
{
    connect(d->service, &domain::MissionService::missionItemChanged, this,
            [this](dto::MissionItemPtr item) { if (item == d->item) this->updateItem(); });
}

MissionItemEditPresenter::~MissionItemEditPresenter()
{}

void MissionItemEditPresenter::setItem(int id)
{
    d->item = d->service->missionItem(id);

    this->updateAvailableCommands();
    this->updateItem();
}

void MissionItemEditPresenter::save()
{
    int commandIndex = this->viewProperty(PROPERTY(commandIndex)).toInt();
    if (commandIndex >= 0 && commandIndex < d->availableCommands.count())
    {
        d->item->setCommand(d->availableCommands.at(commandIndex));
    }
    d->item->setAltitudeRelative(this->viewProperty(PROPERTY(altitudeRelative)).toBool());
    d->item->setCoordinate(this->viewProperty(PROPERTY(position)).value<QGeoCoordinate>());
    d->item->setAltitude(this->viewProperty(PROPERTY(altitude)).toFloat());

    d->item->setParameter(dto::MissionItem::AbortAltitude, this->viewProperty(PROPERTY(abortAltitude)));
    d->item->setParameter(dto::MissionItem::Radius, this->viewProperty(PROPERTY(radius)));
    d->item->setParameter(dto::MissionItem::Repeats, this->viewProperty(PROPERTY(repeats)));
    d->item->setParameter(dto::MissionItem::Time, this->viewProperty(PROPERTY(time)));
    d->item->setParameter(dto::MissionItem::Pitch, this->viewProperty(PROPERTY(pitch)));
    d->item->setParameter(dto::MissionItem::Yaw, this->viewProperty(PROPERTY(yaw)));
    d->item->setParameter(dto::MissionItem::Clockwise, this->viewProperty(PROPERTY(clockwise)));
    d->item->setParameter(dto::MissionItem::IsGroundSpeed, this->viewProperty(PROPERTY(isGroundSpeed)));
    d->item->setParameter(dto::MissionItem::Speed, this->viewProperty(PROPERTY(speedEnabled)).toBool() ?
                              this->viewProperty(PROPERTY(speed)) : QVariant());
    d->item->setParameter(dto::MissionItem::Throttle, this->viewProperty(PROPERTY(throttleEnabled)).toBool() ?
                              this->viewProperty(PROPERTY(throttle)) : QVariant());

    d->item->setStatus(dto::MissionItem::NotActual);

    if (!d->service->save(d->item)) return;
}

void MissionItemEditPresenter::updateItem()
{
    if (d->item)
    {
        int homeAltitude = 0;
        dto::MissionItemPtr home = d->service->missionItem(d->item->missionId(), 0);

        if (home) homeAltitude = home->altitude();
        this->setViewProperty(PROPERTY(homeAltitude), homeAltitude);

        int previousGlobalAltitude = 0;
        bool updateAltitude = d->item->isAltitudedItem();

        QGeoCoordinate previousPosition;
        bool updatePosition = d->item->isPositionatedItem();

        for (int seq = d->item->sequence() - 1; seq >= 0; --seq)
        {
            dto::MissionItemPtr previous = d->service->missionItem(d->item->missionId(), seq);
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

        this->setViewProperty(PROPERTY(sequence), d->item->sequence());
        this->setViewProperty(PROPERTY(command), d->item->command());
        this->setViewProperty(PROPERTY(commandIndex), d->availableCommands.indexOf(d->item->command()));
        this->setViewProperty(PROPERTY(altitudeRelative), d->item->isAltitudeRelative());
        this->setViewProperty(PROPERTY(position), QVariant::fromValue(d->item->coordinate()));
        this->setViewProperty(PROPERTY(altitude), d->item->altitude());
        this->setViewProperty(PROPERTY(abortAltitude), d->item->parameter(dto::MissionItem::AbortAltitude));
        this->setViewProperty(PROPERTY(radius), d->item->parameter(dto::MissionItem::Radius));
        this->setViewProperty(PROPERTY(repeats), d->item->parameter(dto::MissionItem::Repeats));
        this->setViewProperty(PROPERTY(time), d->item->parameter(dto::MissionItem::Time));
        this->setViewProperty(PROPERTY(pitch), d->item->parameter(dto::MissionItem::Pitch));
        this->setViewProperty(PROPERTY(yaw), d->item->parameter(dto::MissionItem::Yaw));
        this->setViewProperty(PROPERTY(clockwise), d->item->parameter(dto::MissionItem::Clockwise));
        this->setViewProperty(PROPERTY(isGroundSpeed), d->item->parameter(dto::MissionItem::IsGroundSpeed));
        this->setViewProperty(PROPERTY(speed), d->item->parameter(dto::MissionItem::Speed));
        this->setViewProperty(PROPERTY(speedEnabled), d->item->parameter(dto::MissionItem::Speed).isValid());
        this->setViewProperty(PROPERTY(throttle), d->item->parameter(dto::MissionItem::Throttle));
        this->setViewProperty(PROPERTY(throttleEnabled), d->item->parameter(dto::MissionItem::Throttle).isValid());
    }
    else
    {
        this->setViewProperty(PROPERTY(sequence), -1);
        this->setViewProperty(PROPERTY(command), dto::MissionItem::UnknownCommand);
    }

    this->setViewProperty(PROPERTY(changed), false);
}

void MissionItemEditPresenter::updateAvailableCommands()
{
    d->updateAvailableCommands();

    QStringList commands;
    for (dto::MissionItem::Command command: d->availableCommands)
    {
        commands.append(d->helper.translateCommand(command));
    }
    this->setViewProperty(PROPERTY(commands), QVariant::fromValue(commands));
}

void MissionItemEditPresenter::updateCommand(int commandIndex)
{
    if (commandIndex > 0 && commandIndex < d->availableCommands.count())
    {
        this->setViewProperty(PROPERTY(command), d->availableCommands.at(commandIndex));
    }
}
