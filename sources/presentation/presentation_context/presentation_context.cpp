#include "presentation_context.h"

// Internal
#include "settings_provider.h"

#include "base_presenter.h"

#include "units.h"
#include "translation_helper.h"

#include "manual_controller.h"

// Qt
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QWindow>
#include <QDebug>

using namespace presentation;

PresentationContext* PresentationContext::lastCreatedContext = nullptr;

PresentationContext::PresentationContext()
{
    PresentationContext::lastCreatedContext = this;

    m_engine = new QQmlApplicationEngine();

    m_engine->addImportPath(QStringLiteral("qrc:/"));

#ifdef WITH_MAPBOXGL
    m_engine->rootContext()->setContextProperty("with_mapboxgl", QVariant(true));
#else
    m_engine->rootContext()->setContextProperty("with_mapboxgl", QVariant(false));
#endif

#ifdef WITH_GAMEPAD
    m_engine->rootContext()->setContextProperty("with_gamepad", QVariant(true));
#else
    m_engine->rootContext()->setContextProperty("with_gamepad", QVariant(false));
#endif

    m_engine->rootContext()->setContextProperty(
                "units", QVariant::fromValue(new utils::Units(m_engine)));
    m_engine->rootContext()->setContextProperty(
                "manual", QVariant::fromValue(new domain::ManualController(m_engine)));
    m_engine->rootContext()->setContextProperty(
                "translator", QVariant::fromValue(new TranslationHelper(m_engine)));

    QObject::connect(m_engine, &QQmlEngine::quit, qApp, &QGuiApplication::quit);
    QObject::connect(qApp, &QGuiApplication::aboutToQuit, qApp, [this]() {
        this->saveWindowedGeometry();
    });
}

PresentationContext::~PresentationContext()
{
    delete m_engine;
}

PresentationContext* PresentationContext::instance()
{
    return lastCreatedContext;
}

QObject* PresentationContext::rootView()
{
    QList<QObject*> list = instance()->m_engine->rootObjects();
    return list.isEmpty() ? nullptr : list.first();
}

QQmlContext* PresentationContext::rootContext()
{
    return instance()->m_engine->rootContext();
}

void PresentationContext::start()
{
    instance()->m_engine->load(QUrl("qrc:/Views/MainView.qml"));
    PresentationContext::updateGeometry();
}

void PresentationContext::updateGeometry()
{
    PresentationContext::updateGeometry(
                settings::Provider::boolValue(settings::gui::fullscreen));
}

void PresentationContext::updateGeometry(bool fullscreen)
{
    QObject* view = PresentationContext::rootView();
    if (!view) return;

    if (fullscreen)
    {
        view->setProperty(PROPERTY(visibility), QWindow::FullScreen);
    }
    else
    {
        QRect rect = settings::Provider::value(settings::gui::geometry).toRect();

        if (rect.isNull())
        {
            view->setProperty(PROPERTY(visibility), QWindow::Maximized);
        }
        else
        {
            view->setProperty(PROPERTY(visibility), QWindow::Windowed);
            view->setProperty(PROPERTY(x), rect.x());
            view->setProperty(PROPERTY(y), rect.y());
            view->setProperty(PROPERTY(width), rect.width());
            view->setProperty(PROPERTY(height), rect.height());
        }
    }
}

void PresentationContext::saveWindowedGeometry()
{
    QObject* view = PresentationContext::rootView();
    if (!view) return;

    if (view->property(PROPERTY(visibility)).value<QWindow::Visibility>() ==
        QWindow::FullScreen) return;

    QRect geometry(view->property(PROPERTY(x)).toInt(),
                   view->property(PROPERTY(y)).toInt(),
                   view->property(PROPERTY(width)).toInt(),
                   view->property(PROPERTY(height)).toInt());
    settings::Provider::setValue(settings::gui::geometry, geometry);
}
