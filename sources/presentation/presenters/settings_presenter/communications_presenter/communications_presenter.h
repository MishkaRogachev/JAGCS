#ifndef COMMUNICATIONS_PRESENTER_H
#define COMMUNICATIONS_PRESENTER_H

#include "base_presenter.h"

namespace domain
{
    class CommunicationManager;
}

namespace presentation
{
    class CommunicationsPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        CommunicationsPresenter(domain::CommunicationManager* manager,
                                QObject* parent);
        ~CommunicationsPresenter() override;

    protected:
        void connectView(QObject* view) override;

    private slots:
        void updateCommunicationsLinks();

        void onAddUdpLink();
        void onAddSerialLink();
        void onChanged();
        void onRemove();

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // COMMUNICATIONS_PRESENTER_H
