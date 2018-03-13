// Qt
#include <QApplication>
#include <QLockFile>
#include <QFontDatabase>
#include <QIcon>
#include <QQmlContext>
#include <QDebug>

// Internal
#include "common.h"
#include "settings_provider.h"

#include "db_manager.h"
#include "service_registry.h"
#include "proxy_manager.h"

#include "presentation_context.h"
#include "translation_manager.h"
#include "gui_style_manager.h"

#include "file_logger.h"

int main(int argc, char* argv[])
{
    QLockFile lock("JAGCS");
    if (!lock.tryLock())
    {
        qFatal("Application JAGCS is locked");
    }

#ifdef Q_OS_WIN32
    QApplication::setAttribute(Qt::AA_UseOpenGLES);
#endif

    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

#ifdef WITH_LOGGER
    qInstallMessageHandler(app::log);
#endif

    presentation::TranslationManager translator;

    int result = 0;
    do
    {
        QApplication app(argc, argv);

        app.setApplicationName("JAGCS");
        app.setOrganizationName("JAGCS");

        QFontDatabase::addApplicationFont(":/fonts/OpenSans-Bold.ttf");
        QFontDatabase::addApplicationFont(":/fonts/OpenSans-Italic.ttf");
        QFontDatabase::addApplicationFont(":/fonts/OpenSans-Regular.ttf");

        app.setFont(QFont("OpenSans"));
        app.setWindowIcon(QIcon(":/icons/jagcs.svg"));

        domain::ProxyManager proxy;
        proxy.load();

        db::DbManager dbManager;
        if (!dbManager.open(settings::Provider::value(settings::data_base::name).toString()))
        {
            qFatal("Unable to establish DB connection");
            app.quit();
        }

        domain::ServiceRegistry registy;
        Q_UNUSED(registy);

        translator.setLocale(settings::Provider::value(settings::gui::locale).toString());

        presentation::PresentationContext context;

        presentation::GuiStyleManager guiStyleManager;
        guiStyleManager.loadSettingsPalette();
        guiStyleManager.loadSettingsSizings();

        context.rootContext()->setContextProperty("settings", settings::Provider::instance());
        context.start();

        result = app.exec();
    } while (result == RESETART_CODE);

    return result;
}
