#ifndef SETTINGS_PROVIDER_H
#define SETTINGS_PROVIDER_H

// Qt
#include <QObject>
#include <QVariant>

namespace domain
{
    class SettingsProvider: public QObject
    {
        Q_OBJECT

    public:
        explicit SettingsProvider(QObject* parent = nullptr);
        ~SettingsProvider() override;

        Q_INVOKABLE QVariant value(const QString& key,
                                   const QVariant& defaultValue = QVariant()) const;

    public slots:
        void setValue(const QString& key, const QVariant& value);

        void beginGroup(const QString& prefix);
        void endGroup();

        void makeDefaults();

    signals:
        void valueChanged(QString key, QVariant value);

    private:
        class Impl;
        Impl* const d;
        Q_DISABLE_COPY(SettingsProvider)
    };
}
#endif // SETTINGS_PROVIDER_H
