#ifndef MANUAL_SETTINGS_PRESENTER_H
#define MANUAL_SETTINGS_PRESENTER_H

#include "base_presenter.h"

namespace presentation
{
    class ManualSettingsPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        explicit ManualSettingsPresenter(QObject* parent = nullptr);

    public slots:
        void update();

    protected:
        void connectView(QObject* view) override;

    private slots:
        void onSetUseJoystick(bool use);
    };
}

#endif // MANUAL_SETTINGS_PRESENTER_H
