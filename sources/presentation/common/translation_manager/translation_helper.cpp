#include "translation_helper.h"

using namespace presentation;

TranslationHelper::TranslationHelper(QObject* parent):
    QObject(parent)
{
    qRegisterMetaType<dto::MissionItem::Command>("dto::MissionItem::Command");
    qRegisterMetaType<dto::Vehicle::Type>("dto::Vehicle::Type");

    qRegisterMetaType<domain::vehicle::Mode>("domain::vehicle::Mode");
    qRegisterMetaType<domain::vehicle::SystemState>("domain::vehicle::SystemState");
}

QString TranslationHelper::translateCommand(dto::MissionItem::Command command)
{
    switch (command)
    {
    case dto::MissionItem::Home: return tr("Home");
    case dto::MissionItem::Takeoff: return tr("Takeoff");
    case dto::MissionItem::Waypoint: return tr("Waypoint");
    case dto::MissionItem::LoiterUnlim: return tr("Loiter unlim.");
    case dto::MissionItem::LoiterAltitude: return tr("Loiter alt.");
    case dto::MissionItem::LoiterTurns: return tr("Loiter turns");
    case dto::MissionItem::LoiterTime: return tr("Loiter time");
    case dto::MissionItem::Continue: return tr("Continue");
    case dto::MissionItem::Return: return tr("Return");
    case dto::MissionItem::Landing: return tr("Landing");
    case dto::MissionItem::SetSpeed: return tr("Set speed");
    case dto::MissionItem::UnknownCommand:
    default: return tr("None");
    }
}

QString TranslationHelper::translateVehicleType(dto::Vehicle::Type type)
{
    switch (type)
    {
    case dto::Vehicle::Auto: return tr("Auto");
    case dto::Vehicle::FixedWing: return tr("Fixed wing");
    case dto::Vehicle::FlyingWing: return tr("Flying wing");
    case dto::Vehicle::Quadcopter: return tr("Quadcopter");
    case dto::Vehicle::Tricopter: return tr("Tricopter");
    case dto::Vehicle::Hexcopter: return tr("Hexcopter");
    case dto::Vehicle::Octocopter: return tr("Octocopter");
    case dto::Vehicle::Helicopter: return tr("Helicopter");
    case dto::Vehicle::Coaxial: return tr("Coaxial");
    case dto::Vehicle::Vtol: return tr("Vtol");
    case dto::Vehicle::Airship: return tr("Airship");
    case dto::Vehicle::Kite: return tr("Kite");
    case dto::Vehicle::Ornithopter: return tr("Ornithopter");
    case dto::Vehicle::UnknownType:
    default: return tr("Unknown");
    }
}

QUrl TranslationHelper::imageFromVehicleType(dto::Vehicle::Type type)
{
    switch (type) {
    case dto::Vehicle::FixedWing:
        return QUrl("qrc:/indicators/fixed_wing_mark.svg");
    case dto::Vehicle::FlyingWing:
        return QUrl("qrc:/indicators/flying_wing_mark.svg");
    case dto::Vehicle::Tricopter:
    case dto::Vehicle::Quadcopter:
    case dto::Vehicle::Hexcopter:
    case dto::Vehicle::Octocopter:
        return QUrl("qrc:/indicators/quadcopter_mark.svg");
    case dto::Vehicle::Helicopter:
    case dto::Vehicle::Coaxial:
        return QUrl("qrc:/indicators/helicopter_mark.svg");
    default:
        return QUrl("qrc:/indicators/unknown_mark.svg");
    }
}

QString TranslationHelper::translateVehicleMode(domain::vehicle::Mode mode)
{
    switch (mode)
    {
    case domain::vehicle::Mode::Acro: return tr("ACRO");
    case domain::vehicle::Mode::Autotune: return tr("AUTOTUN");
    case domain::vehicle::Mode::Avoid: return tr("AVOID");
    case domain::vehicle::Mode::Circle: return tr("CIRCLE");
    case domain::vehicle::Mode::Cruise: return tr("CRUISE");
    case domain::vehicle::Mode::CtrlByAltitude: return tr("CTRL BY ALT");
    case domain::vehicle::Mode::CtrlByAttitude: return tr("CTRL BY ATT");
    case domain::vehicle::Mode::Follow: return tr("FOLLOW");
    case domain::vehicle::Mode::Guided: return tr("GUIDED");
    case domain::vehicle::Mode::HoldPosition: return tr("HOLD");
    case domain::vehicle::Mode::Init: return tr("INIT");
    case domain::vehicle::Mode::Landing: return tr("LAND");
    case domain::vehicle::Mode::Loiter: return tr("LOITER");
    case domain::vehicle::Mode::Manual: return tr("MANUAL");
    case domain::vehicle::Mode::Mission: return tr("MISSION");
    case domain::vehicle::Mode::Return: return tr("RETURN");
    case domain::vehicle::Mode::Stabilize: return tr("STAB");
    case domain::vehicle::Mode::Takeoff: return tr("TAKEOFF");
    case domain::vehicle::Mode::Throw: return tr("THROW");
    case domain::vehicle::Mode::None:
    default: return tr("None");
    }
}

QString TranslationHelper::translateVehicleState(domain::vehicle::SystemState state)
{
    switch (state)
    {
    case domain::vehicle::SystemState::Active: return tr("Active");
    case domain::vehicle::SystemState::Boot: return tr("Boot");
    case domain::vehicle::SystemState::Calibrating: return tr("Calibrating");
    case domain::vehicle::SystemState::Critical: return tr("Critical");
    case domain::vehicle::SystemState::Emergency: return tr("Emergency");
    case domain::vehicle::SystemState::Standby: return tr("Standby");
    case domain::vehicle::SystemState::UnknownState:
    default: return tr("Unknown");
    }
}

QUrl TranslationHelper::imageFromVehicleState(domain::vehicle::SystemState state)
{
    switch (state)
    {
    case domain::vehicle::SystemState::Active: return QUrl("qrc:/indicators/states/active.svg");
    case domain::vehicle::SystemState::Boot: return QUrl("qrc:/indicators/states/boot.svg");
    case domain::vehicle::SystemState::Calibrating: return QUrl("qrc:/indicators/states/calibrating.svg");
    case domain::vehicle::SystemState::Critical: return QUrl("qrc:/indicators/states/critical.svg");
    case domain::vehicle::SystemState::Emergency: return QUrl("qrc:/indicators/states/emergency.svg");
    case domain::vehicle::SystemState::Standby: return QUrl("qrc:/indicators/states/standby.svg");
    case domain::vehicle::SystemState::UnknownState:
    default: return QUrl("qrc:/indicators/states/unknown.svg");
    }
}
