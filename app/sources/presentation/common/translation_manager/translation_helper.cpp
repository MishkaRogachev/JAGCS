#include "translation_helper.h"

using namespace presentation;

TranslationHelper::TranslationHelper(QObject* parent):
    QObject(parent)
{
    qRegisterMetaType<dto::MissionItem::Command>("dto::MissionItem::Command");
    qRegisterMetaType<dto::Vehicle::Type>("dto::Vehicle::Type");

    qRegisterMetaType<data_source::Telemetry::VehicleMode>("data_source::Telemetry::VehicleMode");
    qRegisterMetaType<data_source::Telemetry::SystemState>("data_source::Telemetry::SystemState");
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

QString TranslationHelper::translateVehicleMode(data_source::Telemetry::VehicleMode mode)
{
    switch (mode)
    {
    case data_source::Telemetry::AcroMode: return tr("ACRO");
    case data_source::Telemetry::AutotuneMode: return tr("AUTOTUN");
    case data_source::Telemetry::AvoidMode: return tr("AVOID");
    case data_source::Telemetry::CircleMode: return tr("CIRCLE");
    case data_source::Telemetry::CruiseMode: return tr("CRUISE");
    case data_source::Telemetry::FbwaMode: return tr("FBWA");
    case data_source::Telemetry::FbwbMode: return tr("FBWB");
    case data_source::Telemetry::RattitudeMode: return tr("RATT");
    case data_source::Telemetry::PosCtrlMode: return tr("POS CTRL");
    case data_source::Telemetry::AltCtrlMode: return tr("ALT CTRL");
    case data_source::Telemetry::AltHoldMode: return tr("ALT HOLD");
    case data_source::Telemetry::FollowMode: return tr("FOLLOW");
    case data_source::Telemetry::NavToMode: return tr("NAV TO");
    case data_source::Telemetry::HoldPositionMode: return tr("HOLD");
    case data_source::Telemetry::InitMode: return tr("INIT");
    case data_source::Telemetry::LandingMode: return tr("LAND");
    case data_source::Telemetry::LoiterMode: return tr("LOITER");
    case data_source::Telemetry::ManualMode: return tr("MANUAL");
    case data_source::Telemetry::MissionMode: return tr("MISSION");
    case data_source::Telemetry::ReturnMode: return tr("RETURN");
    case data_source::Telemetry::StabilizeMode: return tr("STAB");
    case data_source::Telemetry::TakeoffMode: return tr("TAKEOFF");
    case data_source::Telemetry::ThrowMode: return tr("THROW");
    case data_source::Telemetry::NoneMode:
    default: return tr("None");
    }
}

QString TranslationHelper::translateVehicleState(data_source::Telemetry::SystemState state)
{
    switch (state)
    {
    case data_source::Telemetry::ActiveState: return tr("Active");
    case data_source::Telemetry::BootState: return tr("Boot");
    case data_source::Telemetry::CalibratingState: return tr("Calibrating");
    case data_source::Telemetry::CriticalState: return tr("Critical");
    case data_source::Telemetry::EmergencyState: return tr("Emergency");
    case data_source::Telemetry::StandbyState: return tr("Standby");
    case data_source::Telemetry::UnknownState:
    default: return tr("Unknown");
    }
}

QUrl TranslationHelper::imageFromVehicleState(data_source::Telemetry::SystemState state)
{
    switch (state)
    {
    case data_source::Telemetry::ActiveState: return QUrl("qrc:/indicators/states/active.svg");
    case data_source::Telemetry::BootState: return QUrl("qrc:/indicators/states/boot.svg");
    case data_source::Telemetry::CalibratingState: return QUrl("qrc:/indicators/states/calibrating.svg");
    case data_source::Telemetry::CriticalState: return QUrl("qrc:/indicators/states/critical.svg");
    case data_source::Telemetry::EmergencyState: return QUrl("qrc:/indicators/states/emergency.svg");
    case data_source::Telemetry::StandbyState: return QUrl("qrc:/indicators/states/standby.svg");
    case data_source::Telemetry::UnknownState:
    default: return QUrl("qrc:/indicators/states/unknown.svg");
    }
}
