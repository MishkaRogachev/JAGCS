#ifndef NETWORK_SETTINGS_PRESENTER_H
#define NETWORK_SETTINGS_PRESENTER_H

#include <QObject>

namespace presentation
{
    class NetworkSettingsPresenter: public QObject
    {
        Q_OBJECT

        Q_PROPERTY(QStringList typeModel READ typeModel NOTIFY typeModelChanged)

    public:
        explicit NetworkSettingsPresenter(QObject* parent = nullptr);
        ~NetworkSettingsPresenter() override;

        QStringList typeModel() const;

    public slots:
        void restore();
        void apply();

    signals:
        void typeModelChanged(QStringList typeModel);

    private:
        class Impl;
        Impl* const d;
    };
}

#endif // NETWORK_SETTINGS_PRESENTER_H
