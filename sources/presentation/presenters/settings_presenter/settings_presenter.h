#ifndef SETTINGS_PRESENTER_H
#define SETTINGS_PRESENTER_H

#include "base_presenter.h"

namespace domain
{
    class DomainEntry;
}

namespace presentation
{
    class SettingsPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        SettingsPresenter(domain::DomainEntry* entry, QObject* view);
        ~SettingsPresenter() override;

        Q_INVOKABLE QObject* createConnectionSettings(QObject* view);
        Q_INVOKABLE QObject* createVideoSettings(QObject* view);
        Q_INVOKABLE QObject* createNetworkSettings(QObject* view);

    private:
        class Impl;
        Impl* const d;
        Q_DISABLE_COPY(SettingsPresenter)
    };
}

#endif // SETTING_SPRESENTER_H
