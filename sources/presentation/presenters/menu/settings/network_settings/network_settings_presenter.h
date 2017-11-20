#ifndef NETWORK_SETTINGS_PRESENTER_H
#define NETWORK_SETTINGS_PRESENTER_H

#include "base_presenter.h"

namespace presentation
{
    class NetworkSettingsPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        explicit NetworkSettingsPresenter(QObject* parent = nullptr);
        ~NetworkSettingsPresenter() override;

    protected:
        void connectView(QObject* view) override;

    private slots:
        void onApply();
        void onRestore();

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // NETWORK_SETTINGS_PRESENTER_H
