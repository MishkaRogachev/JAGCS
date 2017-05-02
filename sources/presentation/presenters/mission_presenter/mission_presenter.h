#ifndef MISSION_PRESENTER_H
#define MISSION_PRESENTER_H

#include "base_presenter.h"

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
        MissionPresenter(domain::DomainEntry* entry,
                         QObject* object = nullptr);
        ~MissionPresenter() override;

    protected:
        void connectView(QObject* view) override;

        void setViewConnected(bool connected);

    private slots:
        void updateMissions();
        void updateAssignment();
        void updateVehicles();
        void updateItem(int sequence);

        void onSelectMission(const QString& name);
        void onAddMission();
        void onRemoveMission();
        void onRenameMission(const QString& name);
        void onAssignVehicle(const QString& name);

        void onAddItem();
        void onRemoveItem();

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // MISSION_PRESENTER_H
