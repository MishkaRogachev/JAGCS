#include "settings_provider.h"

// Qt
#include <QSettings>
#include <QDebug>

// Internal
#include "settings.h"

using namespace domain;

class SettingsProvider::Impl
{
public:
    QSettings settings;
};

SettingsProvider::SettingsProvider():
    d(new Impl())
{
    if (d->settings.allKeys().isEmpty()) this->makeDefaults();
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

void SettingsProvider::setValue(const QString& key, const QVariant& value)
{
    instance()->d->settings.setValue(key, value);
}

void SettingsProvider::beginGroup(const QString& prefix)
{
    instance()->d->settings.beginGroup(prefix);
}

void SettingsProvider::endGroup()
{
    instance()->d->settings.endGroup();
}

void SettingsProvider::makeDefaults()
{
    instance()->d->settings.clear();

    beginGroup(gui_settings::group);
    setValue(gui_settings::toolbarWidth, 320);
    endGroup();

    beginGroup(proxy_settings::group);
    setValue(proxy_settings::type, 0);
    endGroup();

    beginGroup(connection_settings::group);
    setValue(connection_settings::systemId, 255);
    setValue(connection_settings::componentId, 255);
    setValue(connection_settings::baudRate, 57600);
    setValue(connection_settings::hostPort, 14550);
    setValue(connection_settings::address, "127.0.0.1");
    setValue(connection_settings::port, 14551);
    endGroup();
}
