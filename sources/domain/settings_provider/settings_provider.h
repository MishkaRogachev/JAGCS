#ifndef SETTINGS_PROVIDER_H
#define SETTINGS_PROVIDER_H

// Qt
#include <QVariant>

// Internal
#include "settings.h"

namespace domain
{
    class SettingsProvider: public QObject
    {
        Q_OBJECT

    public:
        ~SettingsProvider() override;
        static SettingsProvider* instance();

        Q_INVOKABLE static QVariant value(
                const QString& key, const QVariant& defaultValue = QVariant());
        Q_INVOKABLE static bool boolValue(
                const QString& key, bool defaultValue = false);

        Q_INVOKABLE static void setValue(const QString& key,
                                         const QVariant& value);

        static void makeDefaults();
        static void sync();

    private:
        SettingsProvider();

        class Impl;
        Impl* const d;
        Q_DISABLE_COPY(SettingsProvider)
    };
}
#endif // SETTINGS_PROVIDER_H
