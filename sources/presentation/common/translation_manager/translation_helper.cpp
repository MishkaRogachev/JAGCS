#include "translation_helper.h"

// Qt
#include <QCoreApplication>

using namespace presentation;

TranslationHelper::TranslationHelper(QObject* parent):
    QObject(parent)
{}

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

QString TranslationHelper::translateMode(domain::Mode mode)
{
    switch (mode)
    {
    case domain::Mode::Acro: return tr("ACRO");
    case domain::Mode::Autotune: return tr("AUTOTUN");
    case domain::Mode::Avoid: return tr("AVOID");
    case domain::Mode::Circle: return tr("CIRCLE");
    case domain::Mode::Cruise: return tr("CRUISE");
    case domain::Mode::CtrlByAltitude: return tr("CTRL BY ALT");
    case domain::Mode::CtrlByAttitude: return tr("CTRL BY ATT");
    case domain::Mode::Follow: return tr("FOLLOW");
    case domain::Mode::Guided: return tr("GUIDED");
    case domain::Mode::HoldPosition: return tr("HOLD");
    case domain::Mode::Init: return tr("INIT");
    case domain::Mode::Landing: return tr("LAND");
    case domain::Mode::Loiter: return tr("LOITER");
    case domain::Mode::Manual: return tr("MANUAL");
    case domain::Mode::Mission: return tr("MISSION");
    case domain::Mode::Return: return tr("RETURN");
    case domain::Mode::Stabilize: return tr("STAB");
    case domain::Mode::Takeoff: return tr("TAKEOFF");
    case domain::Mode::Throw: return tr("THROW");
    case domain::Mode::None:
    default: return tr("None");
    }
}
