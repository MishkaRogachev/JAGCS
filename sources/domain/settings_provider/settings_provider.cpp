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

SettingsProvider::SettingsProvider(QObject* parent):
    QObject(parent),
    d(new Impl())
{
    if (d->settings.allKeys().isEmpty()) this->makeDefaults();
}

SettingsProvider::~SettingsProvider()
{
    d->settings.sync();
    delete d;
}

QVariant SettingsProvider::value(const QString& key,
                                 const QVariant& defaultValue) const
{
    return d->settings.value(key, defaultValue);
}

void SettingsProvider::setValue(const QString& key, const QVariant& value)
{
    d->settings.setValue(key, value);
    emit valueChanged(key, value);
}

void SettingsProvider::beginGroup(const QString& prefix)
{
    d->settings.beginGroup(prefix);
}

void SettingsProvider::endGroup()
{
    d->settings.endGroup();
}

void SettingsProvider::makeDefaults()
{
    d->settings.clear();

    this->beginGroup(gui_settings::group);
    this->setValue(gui_settings::toolbarWidth, 320);
    this->endGroup();

    this->beginGroup(proxy_settings::group);
    this->setValue(proxy_settings::type, 0);
    this->endGroup();

    this->beginGroup(connection_settings::group);
    this->setValue(connection_settings::systemId, 255);
    this->setValue(connection_settings::componentId, 255);
    this->setValue(connection_settings::baudRate, 57600);
    this->setValue(connection_settings::hostPort, 14550);
    this->setValue(connection_settings::address, "127.0.0.1");
    this->setValue(connection_settings::port, 14551);
    this->endGroup();
}
