#ifndef COMMAND_PRESENTER_H
#define COMMAND_PRESENTER_H

// Internal
#include "base_presenter.h"
#include "command.h"

namespace presentation
{
    class CommandPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        explicit CommandPresenter(QObject* parent = nullptr);
        ~CommandPresenter() override;

    public slots:
        void setControlVehicle(int vehicleId);

    protected:
        void connectView(QObject* view) override;

    private slots:
        void onExecuteCommand(int commandType, const QVariant& args);
        void onRejectCommand(int commandType);

        void onCommandStatusChanged(domain::Command::CommandType type,
                                    domain::Command::CommandStatus status);

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // COMMAND_PRESENTER_H
