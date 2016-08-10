// Qt
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

// Internal
#include "settings_provider.h"
#include "presenters_factory.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("JAGCS");

    QQmlApplicationEngine engine;

    SettingsProvider settings;
    engine.rootContext()->setContextProperty("settingsProvider", &settings);

    presentation::PresentersFactory factory(&settings);
    engine.rootContext()->setContextProperty("factory", &factory);

    engine.load(QUrl(QStringLiteral("qrc:/Views/MainView.qml")));

    return app.exec();
}
