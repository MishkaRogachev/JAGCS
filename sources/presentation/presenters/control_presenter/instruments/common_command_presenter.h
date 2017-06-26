#ifndef COMMON_COMMAND_PRESENTER_H
#define COMMON_COMMAND_PRESENTER_H

#include "base_presenter.h"

namespace domain
{
    class CommandService;
}

namespace presentation
{
    class CommonCommandPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        CommonCommandPresenter(domain::CommandService* service, int vehicleId,
                               QObject* parent = nullptr);
        ~CommonCommandPresenter() override;

    protected:
        void connectView(QObject* view) override;

    private slots:
        void onCommandArmDisarm(bool arm);

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // COMMON_COMMAND_PRESENTER_H
