#ifndef SETTINGS_PROVIDER_H
#define SETTINGS_PROVIDER_H

// Qt
#include <QVariant>

namespace domain
{
    class SettingsProvider: public QObject
    {
        Q_OBJECT

    public:
        ~SettingsProvider() override;
        static SettingsProvider* instance();

        static QVariant value(const QString& key,
                              const QVariant& defaultValue = QVariant());

        static void setValue(const QString& key, const QVariant& value);

        static void beginGroup(const QString& prefix);
        static void endGroup();

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
