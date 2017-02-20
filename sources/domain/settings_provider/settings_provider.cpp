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
        settings.clear();

        settings.setValue(gui_settings::fullscreen, true);
        settings.setValue(gui_settings::locale, "en");
        settings.setValue(gui_settings::uiSize, 36);
        settings.setValue(gui_settings::paletteStyle, 0);
        settings.setValue(gui_settings::fdRollInverted, 0);

        settings.setValue(map_settings::zoomLevel, 16.0);
        settings.setValue(map_settings::centerLatitude, 55.968954);
        settings.setValue(map_settings::centerLongitude, 37.110155);

        settings.setValue(proxy_settings::type, 0);

        settings.setValue(connection_settings::systemId, 255);
        settings.setValue(connection_settings::componentId, 0);
        settings.setValue(connection_settings::baudRate, 57600);
        settings.setValue(connection_settings::port, 14550);

        settings.setValue(mission_settings::defaultAcceptanceRadius, 3);
        settings.setValue(mission_settings::defaultTakeoffPitch, 15);
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
    delete d;
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
