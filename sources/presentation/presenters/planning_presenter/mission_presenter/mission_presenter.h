#ifndef MISSION_PRESENTER_H
#define MISSION_PRESENTER_H

// Internal
#include "base_presenter.h"
#include "dao_traits.h"

namespace presentation
{
    class MissionPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        explicit MissionPresenter(QObject* parent = nullptr);
        ~MissionPresenter() override;

    public slots:
        void selectMission(const dao::MissionPtr& mission);
        void selectMissionItem(const dao::MissionItemPtr& item);

    protected:
        void connectView(QObject* view) override;
        void setViewConnected(bool connected);

    private slots:
        void onMissionAdded(const dao::MissionPtr& mission);
        void onMissionRemoved(const dao::MissionPtr& mission);
        void onMissionChanged(const dao::MissionPtr& mission);

        void updateMissionsBox();
        void updateVehiclesBox();
        void updateAssignment();

        void onSelectMission(int index);
        void onAddMission();
        void onAddItem();
        void onRemoveMission();
        void onRenameMission(const QString& name);
        void onAssignVehicle(int index);
        void onSetMissionVisible(bool visible);
        void onUploadMission();
        void onDownloadMission();
        void onCancelSyncMission();

    signals:
        void missionSelected(const dao::MissionPtr& mission);
        void missionItemSelected(const dao::MissionItemPtr& item);

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // MISSION_PRESENTER_H
