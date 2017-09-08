// Qt
#include <QApplication>
#include <QLockFile>
#include <QFontDatabase>
#include <QIcon>
#include <QQmlContext>
#include <QDebug>

// Internal
#include "settings_provider.h"

#include "translation_manager.h"
#include "qml_declarations.h"
#include "proxy_manager.h"

#include "service_registry.h"

#include "presentation_context.h"
#include "main_presenter.h"

#include "link_description.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    app.setApplicationName("JAGCS");
    app.setOrganizationName("JAGCS");

    QLockFile lock("JAGCS");
    if (!lock.tryLock())
    {
        qFatal("Application JAGCS is locked");
    }

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

    presentation::PresentationContext::rootContext()->setContextProperty(
                PROPERTY(settings), settings::Provider::instance());
    presenter.setView(presentation::PresentationContext::rootView());

    presenter.setMode("planning");

    return app.exec();
}
