// Qt
#include <QApplication>
#include <QFontDatabase>
#include <QIcon>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDebug>

// Internal
#include "settings_provider.h"

#include "translation_manager.h"
#include "qml_declarations.h"
#include "proxy_manager.h"

#include "service_registry.h"

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

    domain::TranslationManager translations;
    translations.initLocales();

    domain::ProxyManager proxy;
    proxy.load();

    domain::ServiceRegistry::instance()->init(
                settings::Provider::value(settings::data_base::name).toString());

    presentation::MainPresenter presenter;

    registerQmlTypes();
    QQmlApplicationEngine engine(QUrl("qrc:/Views/MainView.qml"));
    engine.rootContext()->setContextProperty(PROPERTY(settings), settings::Provider::instance());
    presenter.setView(engine.rootObjects().first());

    presenter.setMode("planning");

    return app.exec();
}
