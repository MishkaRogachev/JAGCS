// Qt
#include <QApplication>
#include <QLockFile>
#include <QFontDatabase>
#include <QIcon>
#include <QQmlContext>
#include <QDebug>

// Internal
#include "settings_provider.h"

#include "notification_bus.h"
#include "db_manager.h"
#include "serial_device_manager.h"
#include "service_registry.h"
#include "proxy_manager.h"
#include "plugin_manager.h"

#include "presentation_context.h"
#include "translation_manager.h"
#include "gui_style_manager.h"

#ifdef WITH_LOGGER
#include "file_logger.h"
#endif

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

        {
            domain::ProxyManager proxy;
            proxy.load();
        }

        domain::TranslationManager translator;
        translator.setLocale(settings::Provider::value(settings::gui::locale).toString());

        domain::NotificationBus bus;
        Q_UNUSED(bus);

        domain::DbManager manager;
        if (!manager.open(settings::Provider::value(settings::data_base::name).toString()))
        {
            qFatal("Unable to establish DB connection");
            app.quit();
        }

        domain::SerialDeviceManager serialManager;
        Q_UNUSED(serialManager);

        domain::ServiceRegistry registy;
        Q_UNUSED(registy);

        domain::PluginManager plugins;
        plugins.discoverPlugins();
        plugins.restoreConfiguration();

        presentation::PresentationContext context;

        presentation::GuiStyleManager guiStyleManager;
        guiStyleManager.loadSettingsPalette();
        guiStyleManager.loadSettingsSizings();

        context.rootContext()->setContextProperty("settings", settings::Provider::instance());
        context.start();

        result = app.exec();
    } while (result == RESTART_CODE);

    return result;
}
