#ifndef MISSION_PRESENTER_H
#define MISSION_PRESENTER_H

#include "base_presenter.h"

namespace domain
{
    class MissionService;
}

namespace presentation
{
    class MissionPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        MissionPresenter(domain::MissionService* missionService,
                         QObject* object);
        ~MissionPresenter() override;

    public slots:
        void updateMissions();
        void updateMissionItems();

    protected:
        void connectView(QObject* view) override;

    private slots:
        void onMissionSelected(const QString& missionName);
        void onAddMissionItem();
        void onRemoveMissionItem(QObject* item);

    private:
        class Impl;
        Impl* const d;
    };
}

#endif // MISSIONPRESENTER_H
