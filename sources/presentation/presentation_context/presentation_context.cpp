#include "presentation_context.h"

// Internal
#include "settings_provider.h"

#include "vehicle.h"
#include "link_description.h"
#include "mission.h"
#include "mission_assignment.h"
#include "mission_item.h"
#include "video_source.h"
#include "modes.h"
#include "command.h"
#include "log_message.h"

#include "translation_helper.h"

#include "topbar_presenter.h"
#include "location_map_presenter.h"
#include "active_video_presenter.h"
#include "link_list_presenter.h"
#include "link_presenter.h"
#include "vehicle_list_presenter.h"
#include "vehicle_presenter.h"
#include "planning_presenter.h"
#include "mission_list_presenter.h"
#include "mission_presenter.h"
#include "mission_item_edit_presenter.h"
#include "database_presenter.h"
#include "gui_settings_presenter.h"
#include "joystick_settings_presenter.h"
#include "map_settings_presenter.h"
#include "network_settings_presenter.h"
#include "video_settings_presenter.h"
#include "about_presenter.h"

// Qt
#include <QGuiApplication>
#include <QQuickView>
#include <QQuickItem>
#include <QQmlContext>
#include <QQmlEngine>
#include <QDebug>

using namespace presentation;

PresentationContext::PresentationContext()
{
    this->registerQuickTypes();

    m_view = new QQuickView();
    m_view->setResizeMode(QQuickView::SizeRootObjectToView);
    m_view->rootContext()->setContextProperty("translator",
                                              QVariant::fromValue(new TranslationHelper(qApp)));

    QObject::connect(m_view->engine(), &QQmlEngine::quit, qApp, &QGuiApplication::quit);
}

PresentationContext::~PresentationContext()
{
    PresentationContext::saveWindowedGeometry();
    m_view->deleteLater();
}

PresentationContext* PresentationContext::instance()
{
    static PresentationContext context;
    return &context;
}

QObject* PresentationContext::rootView()
{
    return instance()->m_view->rootObject();
}

QQmlContext* PresentationContext::rootContext()
{
    return instance()->m_view->rootContext();
}

void PresentationContext::start()
{
    instance()->m_view->setSource(QUrl("qrc:/Views/MainView.qml")); // TODO: wait objectCreated

    PresentationContext::show();
}

void PresentationContext::show()
{
    if (settings::Provider::boolValue(settings::gui::fullscreen))
    {
        PresentationContext::showFullscreen();
    }
    else
    {
        PresentationContext::showWindowed();
    }
}

void PresentationContext::showFullscreen()
{
    instance()->m_view->showFullScreen();
}

void PresentationContext::showWindowed()
{
    QRect rect = settings::Provider::value(settings::gui::geometry).toRect();

    if (rect.isNull())
    {
        instance()->m_view->showMaximized();
    }
    else
    {
        instance()->m_view->setGeometry(rect);
        instance()->m_view->show();
    }
}

void PresentationContext::saveWindowedGeometry()
{
    if (instance()->m_view->windowState() & Qt::WindowFullScreen) return;
    settings::Provider::setValue(settings::gui::geometry, instance()->m_view->geometry());
}

void PresentationContext::registerQuickTypes()
{
    qmlRegisterUncreatableType<dao::Vehicle>(
                "JAGCS", 1, 0, "Vehicle", "Can't create entities in QML");
    qmlRegisterUncreatableType<dao::LinkDescription>(
                "JAGCS", 1, 0, "LinkDescription", "Can't create entities in QML");
    qmlRegisterUncreatableType<dao::Mission>(
                "JAGCS", 1, 0, "Mission", "Can't create entities in QML");
    qmlRegisterUncreatableType<dao::MissionAssignment>(
                "JAGCS", 1, 0, "MissionAssignment", "Can't create entities in QML");
    qmlRegisterUncreatableType<dao::MissionItem>(
                "JAGCS", 1, 0, "MissionItem", "Can't create entities in QML");
    qmlRegisterUncreatableType<dao::VideoSource>(
                "JAGCS", 1, 0, "VideoSource", "Can't create entities in QML");
    qmlRegisterUncreatableType<domain::Command>(
                "JAGCS", 1, 0, "Command", "Can't create commands in QML");
    qmlRegisterUncreatableType<domain::LogMessage>(
                "JAGCS", 1, 0, "LogMessage", "Can't create log messages in QML");

    qmlRegisterUncreatableMetaObject(domain::staticMetaObject, "JAGCS", 1, 0, "Domain",
                                     "Can't create enums in QML");

    qmlRegisterType<TopbarPresenter>("JAGCS", 1, 0, "TopbarPresenter");
    qmlRegisterType<LocationMapPresenter>("JAGCS", 1, 0, "MapPresenter");
    qmlRegisterType<ActiveVideoPresenter>("JAGCS", 1, 0, "VideoPresenter");
    qmlRegisterType<LinkListPresenter>("JAGCS", 1, 0, "LinkListPresenter");
    qmlRegisterType<LinkPresenter>("JAGCS", 1, 0, "LinkPresenter");
    qmlRegisterType<VehicleListPresenter>("JAGCS", 1, 0, "VehicleListPresenter");
    qmlRegisterType<VehiclePresenter>("JAGCS", 1, 0, "VehiclePresenter");
    qmlRegisterType<PlanningPresenter>("JAGCS", 1, 0, "PlanningPresenter");
    qmlRegisterType<MissionListPresenter>("JAGCS", 1, 0, "MissionListPresenter");
    qmlRegisterType<MissionPresenter>("JAGCS", 1, 0, "MissionPresenter");
    qmlRegisterType<MissionItemEditPresenter>("JAGCS", 1, 0, "MissionItemEditPresenter");
    qmlRegisterType<DatabasePresenter>("JAGCS", 1, 0, "DatabasePresenter");
    qmlRegisterType<GuiSettingsPresenter>("JAGCS", 1, 0, "GuiSettingsPresenter");
    qmlRegisterType<JoystickSettingsPresenter>("JAGCS", 1, 0, "JoystickSettingsPresenter");
    qmlRegisterType<MapSettingsPresenter>("JAGCS", 1, 0, "MapSettingsPresenter");
    qmlRegisterType<NetworkSettingsPresenter>("JAGCS", 1, 0, "NetworkSettingsPresenter");
    qmlRegisterType<VideoSettingsPresenter>("JAGCS", 1, 0, "VideoSettingsPresenter");
    qmlRegisterType<AboutPresenter>("JAGCS", 1, 0, "AboutPresenter");
}
