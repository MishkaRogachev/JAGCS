#ifndef MISSION_PRESENTER_H
#define MISSION_PRESENTER_H

// Internal
#include "base_presenter.h"
#include "dao_traits.h"

namespace domain
{
    class MissionService;
}

namespace presentation
{
    class MapHandle;

    class MissionPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        explicit MissionPresenter(const dao::MissionPtr& mission, QObject* parent = nullptr);
        ~MissionPresenter() override;

    public slots:
        void updateMission();
        void updateAssignment();

    protected:
        void connectView(QObject* view) override;

    private slots:
        void onRename(const QString& name);
        void onSetMissionVisible(bool visible);
        void onRemove();
        void onAssignVehicle(int id);
        void onUploadMission();
        void onDownloadMission();
        void onCancelSyncMission();

    private:
        domain::MissionService* const m_service;
        dao::MissionPtr m_mission;
    };
}

#endif // MISSION_PRESENTER_H
