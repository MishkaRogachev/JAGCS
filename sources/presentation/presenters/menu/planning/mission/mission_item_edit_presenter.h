#ifndef MISSION_ITEM_EDIT_PRESENTER_H
#define MISSION_ITEM_EDIT_PRESENTER_H

// Internal
#include "base_presenter.h"
#include "dao_traits.h"

namespace presentation
{
    class MapHandle;

    class MissionItemEditPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        explicit MissionItemEditPresenter(MapHandle* handle, QObject* object = nullptr);
        ~MissionItemEditPresenter() override;

    public slots:
        void enablePicker();

        void remove();
        void selectItem(int index); // TODO: remove mission from MissionItemEditPresenter
        void save();
        void updateView();

    protected:
        void connectView(QObject* view) override;

    private slots:
        void updateCount();
        void updateAvailableCommands();
        void onUpdateCommand(int commandIndex);

        void onMissionSelected(const dao::MissionPtr& mission);
        void onMissionItemSelected(const dao::MissionItemPtr& item);

        void onChangeSequence(int sequence);

    private:
         class Impl;
         QScopedPointer<Impl> const d;
    };
}

#endif // MISSION_ITEM_EDIT_PRESENTER_H
