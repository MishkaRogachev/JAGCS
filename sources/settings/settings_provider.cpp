#include "settings_provider.h"

// Qt
#include <QSettings>
#include <QGeoCoordinate>
#include <QDebug>

// Internal
#include "settings.h"

using namespace settings;

class Provider::Impl
{
public:
    QSettings settings;

    Impl():
        settings(QSettings::NativeFormat, QSettings::UserScope, "JAGCS", "JAGCS")
    {}

    void makeDefaults()
    {
        using namespace settings;
        settings.clear();

        settings.setValue(data_base::name, "jagcs_db");

        settings.setValue(communication::systemId, 255);
        settings.setValue(communication::componentId, 0);
        settings.setValue(communication::heartbeat, 1000);
        settings.setValue(communication::timeout, 5000);
        settings.setValue(communication::autoAdd, true);
        settings.setValue(communication::baudRate, 57600);
        settings.setValue(communication::port, 14550);
        settings.setValue(communication::statisticsCount, 120);

        settings.setValue(mission::defaultAcceptanceRadius, 3);
        settings.setValue(mission::defaultTakeoffPitch, 15);

        settings.setValue(map::zoomLevel, 16.0);
        settings.setValue(map::centerLatitude, 55.968954);
        settings.setValue(map::centerLongitude, 37.110155);
        settings.setValue(map::bearing, 0);
        settings.setValue(map::activeMapType, 0);
        settings.setValue(map::tileHost, "http://a.tile.openstreetmap.org/");
        settings.setValue(map::cacheSize, 52428800);
        settings.setValue(map::highdpiTiles, true);
        settings.setValue(map::trackLength, 100);

        settings.setValue(gui::fullscreen, true);
        settings.setValue(gui::locale, "en");
        settings.setValue(gui::uiSize, 36);
        settings.setValue(gui::paletteStyle, 0);
        settings.setValue(gui::fdRollInverted, 0);
        settings.setValue(gui::fdSpeedStep, 5);
        settings.setValue(gui::fdSpeedUnits, 0);
        settings.setValue(gui::fdAltitudeStep, 10);
        settings.setValue(gui::fdRelativeAltitude, true);
        settings.setValue(gui::coordinatesDms, true);

        settings.setValue(proxy::type, 0);
    }
};

Provider::Provider():
    d(new Impl())
{
    if (d->settings.allKeys().isEmpty()) d->makeDefaults();
}

Provider::~Provider()
{
    d->settings.sync();
}

Provider* Provider::instance()
{
    static Provider settings;
    return &settings;
}

QVariant Provider::value(const QString& key, const QVariant& defaultValue)
{
    return instance()->d->settings.value(key, defaultValue);
}

bool Provider::boolValue(const QString& key, bool defaultValue)
{
    return Provider::value(key, defaultValue).toBool();
}

void Provider::setValue(const QString& key, const QVariant& value)
{
    instance()->d->settings.setValue(key, value);
}

void Provider::remove(const QString& key)
{
    instance()->d->settings.remove(key);
}

void Provider::makeDefaults()
{
    instance()->d->makeDefaults();
}

void Provider::sync()
{
    instance()->d->settings.sync();
}
