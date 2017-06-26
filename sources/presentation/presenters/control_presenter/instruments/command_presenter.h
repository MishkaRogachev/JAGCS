#ifndef COMMAND_PRESENTER_H
#define COMMAND_PRESENTER_H

#include "base_presenter.h"

namespace domain
{
    class CommandService;
}

namespace presentation
{
    class CommandPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        CommandPresenter(domain::CommandService* service, int vehicleId,
                         QObject* parent = nullptr);
        ~CommandPresenter() override;

    protected:
        void connectView(QObject* view) override;

    private slots:
        void onCommandArmDisarm(bool arm);

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // COMMAND_PRESENTER_H
