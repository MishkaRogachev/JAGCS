#ifndef QML_TYPES_H
#define QML_TYPES_H

// Internal
#include "vehicle.h"
#include "link_description.h"
#include "mission.h"
#include "mission_assignment.h"
#include "mission_item.h"
#include "video_source.h"
#include "vehicle_types.h"
#include "command.h"
#include "notification.h"

#include "manual_controller.h"

#include "topbar_presenter.h"
#include "clock_presenter.h"
#include "radio_status_presenter.h"
#include "connection_presenter.h"
#include "notifications_presenter.h"
#include "location_map_presenter.h"
#include "active_video_presenter.h"
#include "dashboard_presenter.h"
#include "vehicles_list_display_presenter.h"
#include "aerial_vehicle_display_presenter.h"
#include "vertical_profile_presenter.h"
#include "drawer_presenter.h"
#include "link_list_presenter.h"
#include "link_presenter.h"
#include "link_edit_presenter.h"
#include "vehicle_list_presenter.h"
#include "vehicle_presenter.h"
#include "planning_presenter.h"
#include "mission_list_presenter.h"
#include "mission_presenter.h"
#include "mission_edit_presenter.h"
#include "mission_item_list_presenter.h"
#include "mission_item_edit_presenter.h"
#include "mission_assignment_presenter.h"
#include "database_presenter.h"
#include "gui_settings_presenter.h"
#include "joystick_settings_presenter.h"
#include "map_settings_presenter.h"
#include "network_settings_presenter.h"
#include "video_source_list_presenter.h"
#include "video_source_presenter.h"
#include "about_presenter.h"

// Qt
#include <QCoreApplication>
#include <QQmlEngine>
#include <QDebug>

#define POINTERIZE(A) #A"*"
#define META_TYPE(T) qRegisterMetaType<T*>(POINTERIZE(T));
#define QML_TYPE(T) qmlRegisterType<T>("JAGCS", 1, 0, #T);
#define QML_TYPE2(T) META_TYPE(T) QML_TYPE(T)
#define QML_UNCREATABLE_TYPE(T) qmlRegisterUncreatableType<T>("JAGCS", 1, 0, #T, QString(#T) + " is not available in QML.");

using namespace dto;
using namespace domain;
using namespace presentation;

static void registerTypes()
{
    QML_UNCREATABLE_TYPE(Vehicle);
    QML_UNCREATABLE_TYPE(LinkDescription);
    QML_UNCREATABLE_TYPE(Mission);
    QML_UNCREATABLE_TYPE(MissionAssignment);
    QML_UNCREATABLE_TYPE(MissionItem);
    QML_UNCREATABLE_TYPE(Command);
    QML_UNCREATABLE_TYPE(VideoSource);
    QML_UNCREATABLE_TYPE(Notification);

    qmlRegisterUncreatableMetaObject(domain::vehicle::staticMetaObject, "JAGCS", 1, 0, "Domain",
                                     "Can't create enums in QML");

    QML_UNCREATABLE_TYPE(ManualController);

    QML_TYPE(TopbarPresenter);
    QML_TYPE(ClockPresenter);
    QML_TYPE(RadioStatusPresenter);
    QML_TYPE(NotificationsPresenter);
    QML_TYPE(ConnectionPresenter);
    QML_TYPE(LocationMapPresenter);
    QML_TYPE(ActiveVideoPresenter);
    QML_TYPE(DashboardPresenter);
    QML_TYPE(VerticalProfilePresenter);
    QML_TYPE(VehiclesListDisplayPresenter);
    QML_TYPE(AerialVehicleDisplayPresenter);
    QML_TYPE(DrawerPresenter);
    QML_TYPE(LinkListPresenter);
    QML_TYPE(LinkPresenter);
    QML_TYPE(LinkEditPresenter);
    QML_TYPE(VehicleListPresenter);
    QML_TYPE(VehiclePresenter);

    QML_TYPE(PlanningPresenter);
    QML_TYPE2(MissionListPresenter);
    QML_TYPE2(MissionPresenter);
    QML_TYPE2(MissionEditPresenter);
    QML_TYPE2(MissionItemListPresenter);
    QML_TYPE2(MissionItemEditPresenter);
    QML_TYPE2(MissionAssignmentPresenter);

    QML_TYPE(DatabasePresenter);
    QML_TYPE(GuiSettingsPresenter);
    QML_TYPE(JoystickSettingsPresenter);
    QML_TYPE(MapSettingsPresenter);
    QML_TYPE(NetworkSettingsPresenter);
    QML_TYPE(VideoSourceListPresenter);
    QML_TYPE(VideoSourcePresenter);
    QML_TYPE(AboutPresenter);
}

Q_COREAPP_STARTUP_FUNCTION(registerTypes)

#endif // QML_TYPES_H
