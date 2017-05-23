#include "settings_provider.h"

// Qt
#include <QSettings>
#include <QGeoCoordinate>
#include <QDebug>

// Internal
#include "settings.h"

using namespace domain;

class SettingsProvider::Impl
{
public:
    QSettings settings;

    void makeDefaults()
    {
        using namespace settings;
        settings.clear();

        settings.setValue(data_base::name, "jagcs_db");

        settings.setValue(gui::fullscreen, true);
        settings.setValue(gui::locale, "en");
        settings.setValue(gui::uiSize, 36);
        settings.setValue(gui::paletteStyle, 0);
        settings.setValue(gui::fdRollInverted, 0);

        settings.setValue(map::zoomLevel, 16.0);
        settings.setValue(map::centerLatitude, 55.968954);
        settings.setValue(map::centerLongitude, 37.110155);

        settings.setValue(proxy::type, 0);

        settings.setValue(communication::systemId, 255);
        settings.setValue(communication::componentId, 0);
        settings.setValue(communication::autoAdd, true);
        settings.setValue(communication::baudRate, 57600);
        settings.setValue(communication::port, 14550);
        settings.setValue(communication::statisticsCount, 20);

        settings.setValue(telemetry::timeout, 1000);

        settings.setValue(mission::defaultAcceptanceRadius, 3);
        settings.setValue(mission::defaultTakeoffPitch, 15);
    }
};

SettingsProvider::SettingsProvider():
    d(new Impl())
{
    if (d->settings.allKeys().isEmpty()) d->makeDefaults();
}

SettingsProvider::~SettingsProvider()
{
    d->settings.sync();
}

SettingsProvider* SettingsProvider::instance()
{
    static SettingsProvider settings;
    return &settings;
}

QVariant SettingsProvider::value(const QString& key,
                                 const QVariant& defaultValue)
{
    return instance()->d->settings.value(key, defaultValue);
}

bool SettingsProvider::boolValue(const QString& key, bool defaultValue)
{
    return SettingsProvider::value(key, defaultValue).toBool();
}

void SettingsProvider::setValue(const QString& key, const QVariant& value)
{
    instance()->d->settings.setValue(key, value);
}

void SettingsProvider::makeDefaults()
{
    instance()->d->makeDefaults();
}

void SettingsProvider::sync()
{
    instance()->d->settings.sync();
}
