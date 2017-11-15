#ifndef MISSION_PRESENTER_H
#define MISSION_PRESENTER_H

// Internal
#include "base_presenter.h"
#include "dao_traits.h"

namespace presentation
{
    class MapHandle;

    class MissionPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        explicit MissionPresenter(MapHandle* handle, QObject* parent = nullptr);
        ~MissionPresenter() override;

    protected:
        void connectView(QObject* view) override;
        void setViewConnected(bool connected);

    private slots:
        void onMissionAdded(const dao::MissionPtr& mission);
        void onMissionRemoved(const dao::MissionPtr& mission);
        void onMissionChanged(const dao::MissionPtr& mission);

        void onMissionSelected(const dao::MissionPtr& mission);

        void updateMissionsBox();
        void updateVehiclesBox();
        void updateAssignment();

        void onSelectMission(int index);
        void onAddMission();
        void onAddItem(int command);
        void onRemoveMission();
        void onRenameMission(const QString& name);
        void onAssignVehicle(int index);
        void onSetMissionVisible(bool visible);
        void onUploadMission();
        void onDownloadMission();
        void onCancelSyncMission();

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // MISSION_PRESENTER_H
