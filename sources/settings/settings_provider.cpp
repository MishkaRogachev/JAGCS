#include "settings_provider.h"

// Qt
#include <QSettings>
#include <QGeoCoordinate>
#include <QDebug>

// Internal
#include "units.h"

#ifndef INT16_MAX
// Std
#include <limits.h>

#define INT16_MAX std::numeric_limits<std::int16_t>::max()
#endif

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
        { communication::udpPort, 14550 },
        { communication::tcpPort, 5763 },
        { communication::tcpAddress, "127.0.0.1" },
        { communication::bluetoothAddress, "00:00:00:00:00:00" },
        { communication::statisticsCount, 50 },

        { parameters::defaultAcceptanceRadius, 3 },
        { parameters::defaultTakeoffPitch, 15 },
        { parameters::defaultTakeoffAltitude, 50 },
        { parameters::minAltitude, -500 }, // 418 m Daed Sea shore
        { parameters::maxAltitude, 50000 },
        { parameters::precisionAltitude, 1 },
        { parameters::minSpeed, 0 },
        { parameters::maxSpeed, 5000 },
        { parameters::precisionSpeed, 1 },
        { parameters::maxRadius, INT16_MAX },
        { parameters::maxDistance, INT16_MAX },

        { map::zoomLevel, 16.0 },
        { map::centerLatitude, 55.968954 },
        { map::centerLongitude, 37.110155 },
        { map::bearing, 0 },
        { map::tilt, 0 },
        { map::plugin, 0 },
        { map::osmActiveMapType, 0 },
        { map::mapBoxActiveMapType, 0 },
        { map::esriActiveMapType, 0 },
        { map::tileHost, "http://a.tile.openstreetmap.org/" },
        { map::cacheSize, 52428800 },
        { map::highdpiTiles, true },
        { map::trackLength, 100 },

        { video::activeVideo, -1 },

        { manual::enabled, false },
        { manual::interval, 200 },
        { manual::joystick::enabled, false },
        { manual::joystick::device, 0 },
        { manual::joystick::pitch::axis, 2 },
        { manual::joystick::pitch::factor, -5 },
        { manual::joystick::roll::axis, 1 },
        { manual::joystick::roll::factor, 5 },
        { manual::joystick::throttle::axis, 3 },
        { manual::joystick::throttle::factor, 5 },
        { manual::joystick::yaw::axis, 4 },
        { manual::joystick::yaw::factor, 5 },

    #ifdef Q_OS_ANDROID
        { gui::uiSize, 28 },
        { gui::fullscreen, true },
    #else
        { gui::uiSize, 36 },
        { gui::fullscreen, false },
    #endif
        { gui::locale, "en" },
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
    if (!instance()->d->settings.contains(key))
    {
        instance()->d->settings.setValue(key, ::defaultSettings.value(key));
    }
    return instance()->d->settings.value(key);
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
