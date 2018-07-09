#include "translation_helper.h"

using namespace presentation;

TranslationHelper::TranslationHelper(QObject* parent):
    QObject(parent)
{
    qRegisterMetaType<dto::MissionItem::Command>("dto::MissionItem::Command");
    qRegisterMetaType<dto::Vehicle::Type>("dto::Vehicle::Type");

    qRegisterMetaType<domain::Telemetry::VehicleMode>("domain::Telemetry::VehicleMode");
    qRegisterMetaType<domain::Telemetry::SystemState>("domain::Telemetry::SystemState");
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

QString TranslationHelper::translateVehicleMode(domain::Telemetry::VehicleMode mode)
{
    switch (mode)
    {
    case domain::Telemetry::AcroMode: return tr("ACRO");
    case domain::Telemetry::AutotuneMode: return tr("AUTOTUN");
    case domain::Telemetry::AvoidMode: return tr("AVOID");
    case domain::Telemetry::CircleMode: return tr("CIRCLE");
    case domain::Telemetry::CruiseMode: return tr("CRUISE");
    case domain::Telemetry::FbwaMode: return tr("FBWA");
    case domain::Telemetry::FbwbMode: return tr("FBWB");
    case domain::Telemetry::RattitudeMode: return tr("RATT");
    case domain::Telemetry::PosCtrlMode: return tr("POS CTRL");
    case domain::Telemetry::AltCtrlMode: return tr("ALT CTRL");
    case domain::Telemetry::AltHoldMode: return tr("ALT HOLD");
    case domain::Telemetry::FollowMode: return tr("FOLLOW");
    case domain::Telemetry::NavToMode: return tr("NAV TO");
    case domain::Telemetry::HoldPositionMode: return tr("HOLD");
    case domain::Telemetry::InitMode: return tr("INIT");
    case domain::Telemetry::LandingMode: return tr("LAND");
    case domain::Telemetry::LoiterMode: return tr("LOITER");
    case domain::Telemetry::ManualMode: return tr("MANUAL");
    case domain::Telemetry::MissionMode: return tr("MISSION");
    case domain::Telemetry::ReturnMode: return tr("RETURN");
    case domain::Telemetry::StabilizeMode: return tr("STAB");
    case domain::Telemetry::TakeoffMode: return tr("TAKEOFF");
    case domain::Telemetry::ThrowMode: return tr("THROW");
    case domain::Telemetry::NoneMode:
    default: return tr("None");
    }
}

QString TranslationHelper::translateVehicleState(domain::Telemetry::SystemState state)
{
    switch (state)
    {
    case domain::Telemetry::ActiveState: return tr("Active");
    case domain::Telemetry::BootState: return tr("Boot");
    case domain::Telemetry::CalibratingState: return tr("Calibrating");
    case domain::Telemetry::CriticalState: return tr("Critical");
    case domain::Telemetry::EmergencyState: return tr("Emergency");
    case domain::Telemetry::StandbyState: return tr("Standby");
    case domain::Telemetry::UnknownState:
    default: return tr("Unknown");
    }
}

QUrl TranslationHelper::imageFromVehicleState(domain::Telemetry::SystemState state)
{
    switch (state)
    {
    case domain::Telemetry::ActiveState: return QUrl("qrc:/indicators/states/active.svg");
    case domain::Telemetry::BootState: return QUrl("qrc:/indicators/states/boot.svg");
    case domain::Telemetry::CalibratingState: return QUrl("qrc:/indicators/states/calibrating.svg");
    case domain::Telemetry::CriticalState: return QUrl("qrc:/indicators/states/critical.svg");
    case domain::Telemetry::EmergencyState: return QUrl("qrc:/indicators/states/emergency.svg");
    case domain::Telemetry::StandbyState: return QUrl("qrc:/indicators/states/standby.svg");
    case domain::Telemetry::UnknownState:
    default: return QUrl("qrc:/indicators/states/unknown.svg");
    }
}
