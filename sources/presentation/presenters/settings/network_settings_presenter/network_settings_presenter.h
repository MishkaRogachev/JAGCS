#ifndef NETWORK_SETTINGS_PRESENTER_H
#define NETWORK_SETTINGS_PRESENTER_H

#include "base_presenter.h"

namespace domain
{
    class SettingsProvider;
}

namespace presentation
{
    class NetworkSettingsPresenter: public BasePresenter
    {
        Q_OBJECT

        Q_PROPERTY(QStringList typeModel READ typeModel NOTIFY typeModelChanged)

    public:
        explicit NetworkSettingsPresenter(domain::SettingsProvider* settings,
                                          QObject* view);
        ~NetworkSettingsPresenter() override;

        QStringList typeModel() const;

    public slots:
        void restore();
        void apply();

        void updateProxy();

    signals:
        void typeModelChanged(QStringList typeModel);

    private:
        class Impl;
        Impl* const d;
    };
}

#endif // NETWORK_SETTINGS_PRESENTER_H
