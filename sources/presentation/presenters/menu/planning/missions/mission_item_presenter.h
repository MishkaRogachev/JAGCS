#ifndef MISSION_ITEM_PRESENTER_H
#define MISSION_ITEM_PRESENTER_H

// Internal
#include "base_presenter.h"
#include "dao_traits.h"

namespace domain
{
    class MissionService;
}

namespace presentation
{
    class MissionItemPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        explicit MissionItemPresenter(QObject* parent = nullptr);

    public slots:
        void setItem(int id);
        void updateItem();

    private:
        domain::MissionService* const m_service;
        dao::MissionItemPtr m_item;
    };
}

#endif // MISSION_ITEM_PRESENTER_H
