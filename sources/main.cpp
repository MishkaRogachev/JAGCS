// Qt
#include <QApplication>
#include <QFontDatabase>
#include <QIcon>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDebug>

// Internal
#include "domain_entry.h"
#include "settings.h"
#include "settings_provider.h"
#include "translation_manager.h"

#include "main_presenter.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    app.setApplicationName("JAGCS");
    app.setOrganizationName("JAGCS");

    QFontDatabase::addApplicationFont(":/fonts/OpenSans-Bold.ttf");
    QFontDatabase::addApplicationFont(":/fonts/OpenSans-Italic.ttf");
    QFontDatabase::addApplicationFont(":/fonts/OpenSans-Regular.ttf");

    app.setFont(QFont("OpenSans"));

    app.setWindowIcon(QIcon(":/icons/jagcs.svg"));

    domain::SettingsProvider::instance(); // force main thread instance
    domain::TranslationManager::init();

    domain::DomainEntry entry;
    presentation::MainPresenter presenter(&entry);

    QQmlApplicationEngine engine(QUrl("qrc:/Views/MainView.qml"));
    engine.rootContext()->setContextProperty(
                PROPERTY(settings), domain::SettingsProvider::instance());
    presenter.setView(engine.rootObjects().first());

    presenter.setMode("mission");

    return app.exec();
}
