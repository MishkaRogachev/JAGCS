// Qt
#include <QApplication>
#include <QLockFile>
#include <QFontDatabase>
#include <QIcon>
#include <QQmlContext>
#include <QDebug>

// Internal
#include "settings_provider.h"

#include "service_registry.h"
#include "proxy_manager.h"

#include "presentation_context.h"
#include "translation_manager.h"
#include "palette_manager.h"
#include "unified_presenter.h"

#include "link_description.h"

int main(int argc, char* argv[])
{
    #ifdef Q_OS_WIN32
    QApplication::setAttribute(Qt::AA_UseOpenGLES);
    #endif

    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

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

    domain::ProxyManager proxy;
    proxy.load();

    domain::ServiceRegistry::instance()->init(
                settings::Provider::value(settings::data_base::name).toString());

    presentation::TranslationManager translations;
    translations.initLocales();

    presentation::PaletteManager paletteManager;
    paletteManager.reloadPalette();

    presentation::UnifiedPresenter presenter;

    presentation::PresentationContext::rootContext()->setContextProperty(
                PROPERTY(settings), settings::Provider::instance());

    presentation::PresentationContext::load();
    presenter.setView(presentation::PresentationContext::rootView());

    presentation::PresentationContext::show();

    return app.exec();
}
