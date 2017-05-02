#ifndef MISSION_ITEM_PRESENTER_H
#define MISSION_ITEM_PRESENTER_H

// Internal
#include "base_presenter.h"
#include "db_traits.h"

namespace domain
{
    class DomainEntry;
}

namespace presentation
{
    class MissionItemPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        MissionItemPresenter(QObject* object = nullptr);

    public slots:
        void setMissionItem(const db::MissionItemPtr& item);

    protected:
        void connectView(QObject* view) override;

    private slots:
        void update();

    private:
         db::MissionItemPtr m_item;
    };
}

#endif // MISSION_ITEM_PRESENTER_H
