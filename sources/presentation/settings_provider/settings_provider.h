#ifndef SETTINGS_PROVIDER_H
#define SETTINGS__PROVIDER_H

#include <QObject>

namespace presentation
{
    class SettingsProvider: public QObject
    {
        Q_OBJECT

    public:
        explicit SettingsProvider(QObject* parent = nullptr);
        ~SettingsProvider() override;

        Q_INVOKABLE QVariant value(const QString& key) const;

    public slots:
        void setValue(const QString& key, const QVariant& value);

        void beginGroup(const QString& prefix);
        void endGroup();

    signals:
        void valueChanged(QString key, QVariant value);

    private:
        class Impl;
        Impl* const d;
        Q_DISABLE_COPY(SettingsProvider)
    };
}

#endif // SETTINGS_PROVIDER_H
