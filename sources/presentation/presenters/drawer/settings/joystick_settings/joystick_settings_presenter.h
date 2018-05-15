#ifndef JOYSTICK_SETTINGS_PRESENTER_H
#define JOYSTICK_SETTINGS_PRESENTER_H

#include "base_presenter.h"

namespace presentation
{
    class JoystickSettingsPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        explicit JoystickSettingsPresenter(QObject* parent = nullptr);

    public slots:
        void updateView();
        void save();
    };
}

#endif // JOYSTICK_SETTINGS_PRESENTER_H
