#include "settings_provider.h"

#include <QSettings>

class SettingsProvider::Impl
{
public:
    QSettings settings;
};

SettingsProvider::SettingsProvider(QObject* parent):
    QObject(parent),
    d(new Impl())
{}

SettingsProvider::~SettingsProvider()
{
    d->settings.sync();
    delete d;
}

QVariant SettingsProvider::value(const QString& key) const
{
    return d->settings.value(key);
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
