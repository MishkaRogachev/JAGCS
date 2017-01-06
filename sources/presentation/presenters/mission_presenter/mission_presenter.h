#ifndef MISSION_PRESENTER_H
#define MISSION_PRESENTER_H

#include "base_presenter.h"

namespace domain
{
    class MissionService;
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

        void updateCurrentCount(int currentCount);
        void updateTotalCount(int totalCount);

    protected:
        void connectView(QObject* view) override;

    private slots:
        void onVehicleAdded(uint8_t id);
        void onVehicleRemoved(uint8_t id);

        void onMissionSelected(const QString& missionName);
        void onAddMission();
        void onRemoveMission();

        void onAddMissionItem();
        void onRemoveMissionItem(QObject* item);

        void onDownloadMission(const QString& vehicleName);
        void onUploadMission(const QString& vehicleName);

    private:
        class Impl;
        Impl* const d;
    };
}

#endif // MISSIONPRESENTER_H
