// Qt
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>

// Internal
#include "domain_entry.h"
#include "settings_provider.h"

#include "presenters_factory.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("JAGCS");

    QQuickStyle::setStyle("Material");

    QQmlApplicationEngine engine;

    domain::DomainEntry entry;
    engine.rootContext()->setContextProperty("settingsProvider", entry.settings());

    presentation::PresentersFactory factory(&entry);
    engine.rootContext()->setContextProperty("factory", &factory);

    engine.load(QUrl(QStringLiteral("qrc:/Views/MainView.qml")));

    return app.exec();
}
