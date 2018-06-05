#ifndef CLOCK_PRESENTER_H
#define CLOCK_PRESENTER_H

// Internal
#include "base_presenter.h"

namespace presentation
{
    class ClockPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        explicit ClockPresenter(QObject* parent = nullptr);

    public slots:
        void start();
        void stop();
        void updateDateTime();

    protected:
        void timerEvent(QTimerEvent* event);

    private:
        int m_timerId = 0;
    };
}

#endif // CLOCK_PRESENTER_H
