#include "translation_helper.h"

using namespace presentation;

TranslationHelper::TranslationHelper(QObject* parent):
    QObject(parent)
{
    qRegisterMetaType<dao::MissionItem::Command>("dao::MissionItem::Command");
    qRegisterMetaType<dao::Vehicle::Type>("dao::Vehicle::Type");
    qRegisterMetaType<domain::vehicle::Mode>("domain::vehicle::Mode");
}

QString TranslationHelper::translateCommand(dao::MissionItem::Command command)
{
    switch (command)
    {
    case dao::MissionItem::Home: return tr("Home");
    case dao::MissionItem::Takeoff: return tr("Takeoff");
    case dao::MissionItem::Waypoint: return tr("Waypoint");
    case dao::MissionItem::LoiterUnlim: return tr("Loiter unlim.");
    case dao::MissionItem::LoiterAltitude: return tr("Loiter alt.");
    case dao::MissionItem::LoiterTurns: return tr("Loiter turns");
    case dao::MissionItem::LoiterTime: return tr("Loiter time");
    case dao::MissionItem::Continue: return tr("Continue");
    case dao::MissionItem::Return: return tr("Return");
    case dao::MissionItem::Landing: return tr("Landing");
    case dao::MissionItem::SetSpeed: return tr("Set speed");
    case dao::MissionItem::UnknownCommand:
    default: return tr("None");
    }
}

QString TranslationHelper::translateVehicleType(dao::Vehicle::Type type)
{
    switch (type)
    {
    case dao::Vehicle::Auto: return tr("Auto");
    case dao::Vehicle::FixedWing: return tr("Fixed wing");
    case dao::Vehicle::FlyingWing: return tr("Flying wing");
    case dao::Vehicle::Quadcopter: return tr("Quadcopter");
    case dao::Vehicle::Tricopter: return tr("Tricopter");
    case dao::Vehicle::Hexcopter: return tr("Hexcopter");
    case dao::Vehicle::Coaxial: return tr("Coaxial");
    case dao::Vehicle::Vtol: return tr("Vtol");
    case dao::Vehicle::Airship: return tr("Airship");
    case dao::Vehicle::Kite: return tr("Kite");
    case dao::Vehicle::Ornithopter: return tr("Ornithopter");
    case dao::Vehicle::UnknownType:
    default: return tr("Unknown");
    }
}

QUrl TranslationHelper::imageFromVehicleType(dao::Vehicle::Type type)
{
    switch (type) {
    case dao::Vehicle::FixedWing:
        return QUrl("qrc:/indicators/fixed_wing_mark.svg");
    case dao::Vehicle::FlyingWing:
        return QUrl("qrc:/indicators/flying_wing_mark.svg");
    case dao::Vehicle::Tricopter:
    case dao::Vehicle::Quadcopter:
    case dao::Vehicle::Hexcopter:
    case dao::Vehicle::Octocopter:
        return QUrl("qrc:/indicators/quadcopter_mark.svg");
    case dao::Vehicle::Helicopter:
    case dao::Vehicle::Coaxial:
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
    default: return tr("None");
    }
}
