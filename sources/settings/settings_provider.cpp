#include "settings_provider.h"

// Qt
#include <QSettings>
#include <QGeoCoordinate>
#include <QDebug>

// Internal
#include "units.h"

using namespace settings;

namespace
{
    QMap<QString, QVariant> defaultSettings =
    {
        { data_base::name, "jagcs_db" },

        { communication::systemId, 255 },
        { communication::componentId, 0 },
        { communication::heartbeat, 1000 },
        { communication::timeout, 5000 },
        { communication::autoAdd, true },
        { communication::baudRate, 57600 },
        { communication::port, 14550 },
        { communication::statisticsCount, 50 },

        { mission::defaultAcceptanceRadius, 3 },
        { mission::defaultTakeoffPitch, 15 },

        { map::zoomLevel, 16.0 },
        { map::centerLatitude, 55.968954 },
        { map::centerLongitude, 37.110155 },
        { map::bearing, 0 },
        { map::tilt, 0 },
        { map::plugin, 0 },
        { map::osmActiveMapType, 0 },
        { map::mapBoxGlActiveMapType, 5 },
        { map::esriActiveMapType, 0 },
        { map::tileHost, "http://a.tile.openstreetmap.org/" },
        { map::cacheSize, 52428800 },
        { map::highdpiTiles, true },
        { map::trackLength, 100 },

        { video::activeVideo, -1 },

        { manual::enabled, false },
        { manual::interval, 100 },
        { manual::joystick::enabled, false },
        { manual::joystick::device, 0 },
        { manual::joystick::pitchAxis, 1 },
        { manual::joystick::rollAxis, 2 },
        { manual::joystick::yawAxis, 3 },
        { manual::joystick::throttleAxis, 4 },

        { gui::fullscreen, true },
        { gui::locale, "en" },
        { gui::uiSize, 36 },
        { gui::paletteStyle, 0 },
        { gui::fdRollInverted, 0 },
        { gui::fdSpeedStep, 5 },
        { gui::fdSpeedUnits, utils::Units::Mps },
        { gui::fdAltitudeStep, 10 },
        { gui::fdAltitudeUnits, utils::Units::Meters },
        { gui::fdRelativeAltitude, true },
        { gui::vibrationModelCount, 30 },
        { gui::coordinatesDms, true },

        { proxy::type, 0 }
    };
}

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

        for (const QString& key: ::defaultSettings.keys())
        {
            settings.setValue(key, ::defaultSettings[key]);
        }
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

QVariant Provider::value(const QString& key)
{
    return instance()->d->settings.value(key, ::defaultSettings.value(key));
}

bool Provider::boolValue(const QString& key)
{
    return Provider::value(key).toBool();
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
