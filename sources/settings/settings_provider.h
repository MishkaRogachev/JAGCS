#ifndef SETTINGS_PROVIDER_H
#define SETTINGS_PROVIDER_H

// Qt
#include <QVariant>

// Internal
#include "settings.h"

namespace settings
{
    class Provider: public QObject
    {
        Q_OBJECT

    public:
        ~Provider() override;
        static Provider* instance();

        Q_INVOKABLE static QVariant value(const QString& key, const QVariant& defaultValue = QVariant());
        Q_INVOKABLE static bool boolValue(const QString& key, bool defaultValue = false);
        Q_INVOKABLE static void setValue(const QString& key, const QVariant& value);

        static void makeDefaults();
        static void sync();

    private:
        Provider();

        class Impl;
        QScopedPointer<Impl> const d;
        Q_DISABLE_COPY(Provider)
    };
}
#endif // SETTINGS_PROVIDER_H
