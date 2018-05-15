#ifndef MISSION_ITEM_PRESENTER_H
#define MISSION_ITEM_PRESENTER_H

// Internal
#include "base_presenter.h"
#include "dto_traits.h"

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
        dto::MissionItemPtr m_item;
    };
}

#endif // MISSION_ITEM_PRESENTER_H
