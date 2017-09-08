#include "presentation_context.h"

// Qt
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

using namespace presentation;

PresentationContext::PresentationContext():
    m_engine(new QQmlApplicationEngine(QUrl("qrc:/Views/MainView.qml"), qApp))
{}

PresentationContext* PresentationContext::instance()
{
    static PresentationContext context;
    return &context;
}

QObject* PresentationContext::rootView()
{
    return instance()->m_engine->rootObjects().first();
}

QQmlContext* PresentationContext::rootContext()
{
    return instance()->m_engine->rootContext();
}
