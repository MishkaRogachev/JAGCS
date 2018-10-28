#ifndef DRAWER_PRESENTER_H
#define DRAWER_PRESENTER_H

#include "base_presenter.h"

namespace presentation
{
    class DrawerPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        enum Mode
        {
            UnknownMode,
            Home,
                Plan,
                Fleet,
                Connection,
                Logs,
                Settings,
                    Database,
                    Map,
                    Video,
                    Joystick,
                    Gui,
                    Networking,
                About,
                Quit
        };

        explicit DrawerPresenter(QObject* parent = nullptr);

        Q_INVOKABLE QString modeString(Mode mode) const;
        Q_INVOKABLE QUrl modeIcon(Mode mode) const;

    public slots:
        void setMode(Mode mode);
        void home();

    private:
        Q_ENUM(Mode)
    };
}

#endif // DRAWER_PRESENTER_H
