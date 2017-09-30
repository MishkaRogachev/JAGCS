#ifndef MISSION_ITEM_EDIT_PRESENTER_H
#define MISSION_ITEM_EDIT_PRESENTER_H

// Internal
#include "base_presenter.h"
#include "dao_traits.h"

namespace presentation
{
    class MissionItemEditPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        explicit MissionItemEditPresenter(QObject* object = nullptr);
        ~MissionItemEditPresenter() override;

        dao::MissionPtr selectedMission() const;

    public slots:
        void selectMission(const dao::MissionPtr& mission);
        void setPicking(bool picking);

        void remove();
        void selectItem(int index);
        void save();
        void updateView();

    signals:
        void itemSelected(const dao::MissionItemPtr& item);

    protected:
        void connectView(QObject* view) override;

    private slots:
        void updateCount();
        void updateAvailableCommands();
        void onUpdateCommand(int commandIndex);

    private:
         class Impl;
         QScopedPointer<Impl> const d;
    };
}

#endif // MISSION_ITEM_EDIT_PRESENTER_H
