#ifndef MISSION_PRESENTER_H
#define MISSION_PRESENTER_H

#include "base_presenter.h"

namespace domain
{
    class MissionService;
    class AbstractVehicle;
    class VehicleService;
}

namespace presentation
{
    class MissionPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        MissionPresenter(domain::MissionService* missionService,
                         domain::VehicleService* vehicleService,
                         QObject* object);
        ~MissionPresenter() override;

    public slots:
        void updateMissions();
        void updateVehicles();
        void updateMissionItems();
        void updateSelectedVehicle();

        void updateCurrentProgress(int currentProgress);
        void updateTotalProgress(int totalProgress);
        void updateMissionStatus();

    protected:
        void connectView(QObject* view) override;

    private slots:
        void onVehicleAdded(domain::AbstractVehicle* vehicle);
        void onVehicleRemoved(domain::AbstractVehicle* vehicle);

        void onMissionSelected(const QString& missionName);
        void onAddMission();
        void onRemoveMission();

        void onAddMissionItem();
        void onRemoveMissionItem(QObject* item);

        void onVehicleSelected(const QString& vehicleName);
        void onDownloadMission();
        void onUploadMission();

    private:
        class Impl;
        Impl* const d;
    };
}

#endif // MISSIONPRESENTER_H
