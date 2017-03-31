#ifndef COMMUNICATION_LINK_PRESENTER_H
#define COMMUNICATION_LINK_PRESENTER_H

#include "base_presenter.h"

namespace presentation
{
    class CommunicationLinkPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        CommunicationLinkPresenter(QObject* parent);
        ~CommunicationLinkPresenter() override;

    protected:
        void connectView(QObject* view) override;

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // COMMUNICATION_LINK_PRESENTER_H
