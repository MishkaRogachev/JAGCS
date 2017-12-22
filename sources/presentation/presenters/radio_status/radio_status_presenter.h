#ifndef RADIO_STATUS_PRESENTER_H
#define RADIO_STATUS_PRESENTER_H

// Internal
#include "base_presenter.h"

namespace presentation
{
    class RadioStatusPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        explicit RadioStatusPresenter(QObject* parent = nullptr);
        ~RadioStatusPresenter() override;

    public slots:
        void updateParameters();

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // RADIO_STATUS_PRESENTER_H
