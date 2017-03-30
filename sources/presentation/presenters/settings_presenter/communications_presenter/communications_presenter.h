#ifndef COMMUNICATIONS_PRESENTER_H
#define COMMUNICATIONS_PRESENTER_H

#include "base_presenter.h"

namespace domain
{
    class DomainFacade;
}

namespace presentation
{
    class CommunicationsPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        CommunicationsPresenter(QObject* parent);
        ~CommunicationsPresenter() override;

    protected:
        void connectView(QObject* view) override;

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // COMMUNICATIONS_PRESENTER_H
