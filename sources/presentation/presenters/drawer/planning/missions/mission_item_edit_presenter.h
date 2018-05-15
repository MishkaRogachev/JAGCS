#ifndef MISSION_ITEM_EDIT_PRESENTER_H
#define MISSION_ITEM_EDIT_PRESENTER_H

// Internal
#include "base_presenter.h"
#include "dto_traits.h"
#include "mission_item.h"

namespace presentation
{
    class MissionItemEditPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        explicit MissionItemEditPresenter(QObject* object = nullptr);
        ~MissionItemEditPresenter() override;

    public slots:
        void setItem(int id);
        void save();

        void updateItem();
        void updateAvailableCommands();
        void updateCommand(int commandIndex);

    private:
         class Impl;
         QScopedPointer<Impl> const d;
    };
}

#endif // MISSION_ITEM_EDIT_PRESENTER_H
