// Qt
#include <QApplication>
#include <QFontDatabase>
#include <QIcon>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDebug>

// Internal
#include "settings_provider.h"
#include "domain_entry.h"

#include "translation_manager.h"
#include "qml_declarations.h"

#include "main_presenter.h"

#include "link_description.h"

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

    domain::TranslationManager::init();
    registerQmlTypes();

    domain::DomainEntry facade;
    presentation::MainPresenter presenter(&facade);

    QQmlApplicationEngine engine(QUrl("qrc:/Views/MainView.qml"));
    engine.rootContext()->setContextProperty(PROPERTY(settings), settings::Provider::instance());
    presenter.setView(engine.rootObjects().first());

    presenter.setMode("planning");

    return app.exec();
}
