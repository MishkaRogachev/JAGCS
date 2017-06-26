#ifndef MISSION_COMMAND_PRESENTER_H
#define MISSION_COMMAND_PRESENTER_H

#include "base_presenter.h"

namespace domain
{
    class CommandService;
}

namespace presentation
{
    class MissionCommandPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        MissionCommandPresenter(domain::CommandService* service, int vehicleId,
                         QObject* parent = nullptr);
        ~MissionCommandPresenter() override;

    protected:
        void connectView(QObject* view) override;

    private slots:
        void onCommandReturn();
        void onCommandStart();
        void onCommandJumpTo(int item);

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // MISSION_COMMAND_PRESENTER_H
