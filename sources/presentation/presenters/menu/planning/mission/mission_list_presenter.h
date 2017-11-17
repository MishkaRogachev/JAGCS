#ifndef MISSION_LIST_PRESENTER_H
#define MISSION_LIST_PRESENTER_H

// Internal
#include "base_presenter.h"
#include "dao_traits.h"

namespace presentation
{
    class MissionListPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        explicit MissionListPresenter(QObject* parent = nullptr);
        ~MissionListPresenter() override;

    public slots:
        void updateMissions();

    protected:
        void connectView(QObject* view) override;

    private slots:
        void onMissionAdded(const dao::MissionPtr& mission);
        void onMissionRemoved(const dao::MissionPtr& mission);
        void onMissionChanged(const dao::MissionPtr& mission);
        void updateMissionAssignment(const dao::MissionAssignmentPtr& assignment);

        void onAddMission();

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // MISSION_LIST_PRESENTER_H
