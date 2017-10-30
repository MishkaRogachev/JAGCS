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

#include "main_presenter.h"
#include "translation_helper.h"

// Qt
#include <QGuiApplication>
#include <QQuickView>
#include <QQuickItem>
#include <QQmlContext>
#include <QDebug>

using namespace presentation;

PresentationContext::PresentationContext()
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

    qmlRegisterUncreatableType<presentation::MainPresenter>(
                "JAGCS", 1, 0, "MainPresenter", "Can't create presenters in QML");

    qmlRegisterUncreatableMetaObject(domain::staticMetaObject, "JAGCS", 1, 0, "Domain",
                                     "Can't create enums in QML");

    m_view = new QQuickView();
    m_view->rootContext()->setContextProperty("translator",
                                              QVariant::fromValue(new TranslationHelper(qApp)));
}

PresentationContext::~PresentationContext()
{
    PresentationContext::saveGeometry();
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

void PresentationContext::load()
{
    instance()->m_view->setSource(QUrl("qrc:/Views/UnifiedView.qml"));

    // TODO: wait objectCreated
}

void PresentationContext::show()
{
    if (settings::Provider::boolValue(settings::gui::fullscreen))
    {
        instance()->m_view->showFullScreen();
    }
    else
    {
        QRect rect = settings::Provider::value(settings::gui::geometry).toRect();

        if (rect.isNull()) instance()->m_view->showMaximized();
        else
        {
            instance()->m_view->setGeometry(rect);
            instance()->m_view->show();
        }
    }
}

void PresentationContext::saveGeometry()
{
    if (instance()->m_view->windowState() & Qt::WindowFullScreen) return;
    settings::Provider::setValue(settings::gui::geometry, instance()->m_view->geometry());
}
