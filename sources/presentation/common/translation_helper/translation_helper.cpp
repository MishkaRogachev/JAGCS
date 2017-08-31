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
    case dao::MissionItem::Home: return qApp->translate("TranslationHelper", "Home");
    case dao::MissionItem::Takeoff: return qApp->translate("TranslationHelper", "Takeoff");
    case dao::MissionItem::Waypoint: return qApp->translate("TranslationHelper", "Waypoint");
    case dao::MissionItem::LoiterUnlim: return qApp->translate("TranslationHelper", "Loiter unlim.");
    case dao::MissionItem::LoiterAltitude: return qApp->translate("TranslationHelper", "Loiter alt.");
    case dao::MissionItem::LoiterTurns: return qApp->translate("TranslationHelper", "Loiter turns");
    case dao::MissionItem::LoiterTime: return qApp->translate("TranslationHelper", "Loiter time");
    case dao::MissionItem::Continue: return qApp->translate("TranslationHelper", "Continue");
    case dao::MissionItem::Return: return qApp->translate("TranslationHelper", "Return");
    case dao::MissionItem::Landing: return qApp->translate("TranslationHelper", "Landing");
    case dao::MissionItem::SetSpeed: return qApp->translate("TranslationHelper", "Set speed");
    case dao::MissionItem::UnknownCommand:
    default: return qApp->translate("TranslationHelper", "None");
    }
}

QString TranslationHelper::translateVehicleType(dao::Vehicle::Type type)
{
    switch (type)
    {
    case dao::Vehicle::Auto: return qApp->translate("TranslationHelper", "Auto");
    case dao::Vehicle::FixedWing: return qApp->translate("TranslationHelper", "Fixed wing");
    case dao::Vehicle::FlyingWing: return qApp->translate("TranslationHelper", "Flying wing");
    case dao::Vehicle::Quadcopter: return qApp->translate("TranslationHelper", "Quadcopter");
    case dao::Vehicle::Tricopter: return qApp->translate("TranslationHelper", "Tricopter");
    case dao::Vehicle::Hexcopter: return qApp->translate("TranslationHelper", "Hexcopter");
    case dao::Vehicle::Coaxial: return qApp->translate("TranslationHelper", "Coaxial");
    case dao::Vehicle::Vtol: return qApp->translate("TranslationHelper", "Vtol");
    case dao::Vehicle::Airship: return qApp->translate("TranslationHelper", "Airship");
    case dao::Vehicle::Kite: return qApp->translate("TranslationHelper", "Kite");
    case dao::Vehicle::Ornithopter: return qApp->translate("TranslationHelper", "Ornithopter");
    case dao::Vehicle::UnknownType:
    default: return qApp->translate("TranslationHelper", "Unknown");
    }
}
