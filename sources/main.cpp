// Qt
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

// Internal
#include "presenters_factory.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;

    presentation::PresentersFactory factory;
    engine.rootContext()->setContextProperty("factory", &factory);

    engine.load(QUrl(QStringLiteral("qrc:/Views/MainView.qml")));

    return app.exec();
}
