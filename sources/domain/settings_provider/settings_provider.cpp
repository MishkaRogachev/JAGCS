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

    void makeDefaults()
    {
        settings.clear();

        settings.beginGroup(gui_settings::group);
        settings.setValue(gui_settings::toolbarWidth, 320);
        settings.endGroup();

        settings.beginGroup(proxy_settings::group);
        settings.setValue(proxy_settings::type, 0);
        settings.endGroup();

        settings.beginGroup(connection_settings::group);
        settings.setValue(connection_settings::systemId, 255);
        settings.setValue(connection_settings::componentId, 255);
        settings.setValue(connection_settings::baudRate, 57600);
        settings.setValue(connection_settings::hostPort, 14550);
        settings.setValue(connection_settings::address, "127.0.0.1");
        settings.setValue(connection_settings::port, 14551);
        settings.endGroup();
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
    instance()->d->makeDefaults();
}

void SettingsProvider::sync()
{
    instance()->d->settings.sync();
}
