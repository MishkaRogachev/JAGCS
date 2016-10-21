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
        SettingsPresenter(domain::DomainEntry* entry, QObject* parent);
        ~SettingsPresenter() override;

    protected:
        void connectView(QObject* view) override;

    private slots:
        void onMakeDefaults();

    private:
        class Impl;
        Impl* const d;
    };
}

#endif // SETTING_SPRESENTER_H
