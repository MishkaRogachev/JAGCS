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

    public slots:
        void updateView();
        void save();

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // NETWORK_SETTINGS_PRESENTER_H
