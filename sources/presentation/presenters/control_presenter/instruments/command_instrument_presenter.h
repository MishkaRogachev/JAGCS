#ifndef COMMAND_INSTRUMENT_PRESENTER_H
#define COMMAND_INSTRUMENT_PRESENTER_H

// Internal
#include "base_presenter.h"
#include "command.h"

namespace domain
{
    class CommandService;
}

namespace presentation
{
    class CommandInstrumentPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        CommandInstrumentPresenter(int vehicleId, QObject* parent = nullptr);
        ~CommandInstrumentPresenter() override;

    protected:
        void connectView(QObject* view) override;

    private slots:
        void onExecuteCommand(int commandType);
        void onExecuteBoolCommand(int commandType, bool check);
        void onRejectCommand(int commandType);

        void onCommandStatusChanged(domain::Command::CommandType type,
                                    domain::Command::CommandStatus status);

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // COMMAND_INSTRUMENT_PRESENTER_H
