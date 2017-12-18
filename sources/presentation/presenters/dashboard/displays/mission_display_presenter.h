#ifndef MISSION_DISPLAY_PRESENTER_H
#define MISSION_DISPLAY_PRESENTER_H

// Internal
#include "base_display_presenter.h"
#include "dao_traits.h"

namespace domain
{
    class MissionService;
    class CommandService;
}

namespace presentation
{
    class MissionDisplayPresenter: public BaseDisplayPresenter
    {
        Q_OBJECT

    public:
        explicit MissionDisplayPresenter(QObject* parent = nullptr);

    public slots:
        void setVehicle(int vehicleId) override;
        void updateItems();

        void goTo(int index);

    private:
        domain::MissionService* const m_missionService;
        domain::CommandService* const m_commandService;
        dao::MissionAssignmentPtr m_assignment;
    };
}

#endif // MISSION_DISPLAY_PRESENTER_H
