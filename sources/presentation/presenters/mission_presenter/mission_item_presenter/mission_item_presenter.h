#ifndef MISSION_ITEM_PRESENTER_H
#define MISSION_ITEM_PRESENTER_H

#include "base_presenter.h"

namespace domain
{
    class DomainFacade;
}

namespace presentation
{
    class MissionItemPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        MissionItemPresenter(domain::DomainFacade* facade,
                             QObject* object = nullptr);
        ~MissionItemPresenter() override;

    protected:
        void connectView(QObject* view) override;

    private slots:
        void update();

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // MISSION_ITEM_PRESENTER_H
