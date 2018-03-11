#ifndef MISSION_EDIT_PRESENTER_H
#define MISSION_EDIT_PRESENTER_H

// Internal
#include "base_presenter.h"
#include "dto_traits.h"
#include "mission_item.h"

namespace presentation
{
    class MissionEditPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        explicit MissionEditPresenter(QObject* object = nullptr);
        ~MissionEditPresenter() override;

    public slots:
        void setMission(int id);
        void setItem(int id);
        void selectItem(int index);

        void updateCount();
        void updateItem();

        void remove();
        void addItem(dto::MissionItem::Command command);
        void changeSequence(int sequence);

    private:
         class Impl;
         QScopedPointer<Impl> const d;
    };
}

#endif // MISSION_ITEM_EDIT_PRESENTER_H
