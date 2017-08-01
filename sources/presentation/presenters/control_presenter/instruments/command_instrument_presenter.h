#ifndef COMMAND_INSTRUMENT_PRESENTER_H
#define COMMAND_INSTRUMENT_PRESENTER_H

#include "base_presenter.h"

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
        void onCommandReturn();
        void onCommandStart();
        void onPauseContinue(bool unpause);

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // COMMAND_INSTRUMENT_PRESENTER_H
