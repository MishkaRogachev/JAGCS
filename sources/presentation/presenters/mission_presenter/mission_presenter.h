#ifndef MISSION_PRESENTER_H
#define MISSION_PRESENTER_H

// Internal
#include "base_presenter.h"
#include "db_traits.h"

namespace domain
{
    class DomainEntry;
}

namespace presentation
{
    class MissionPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        explicit MissionPresenter(domain::DomainEntry* entry,
                                  QObject* object = nullptr);
        ~MissionPresenter() override;

    public slots:
        void selectMission(const db::MissionPtr& mission);

    protected:
        void connectView(QObject* view) override;
        void setViewConnected(bool connected);

    private slots:
        void onMissionAdded(const db::MissionPtr& mission);
        void onMissionRemoved(const db::MissionPtr& mission);
        void updateMissionsBox();
        void updateAssignment();
        void updateVehicles();

        void onSelectMission(int index);
        void onAddMission();
        void onRemoveMission();
        void onRenameMission(const QString& name);
        void onAssignVehicle(const QString& name);
        void onUploadMission();
        void onDownloadMission();

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // MISSION_PRESENTER_H
