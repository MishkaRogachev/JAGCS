#ifndef VERTICAL_PROFILE_PRESENTER_H
#define VERTICAL_PROFILE_PRESENTER_H

// Internal
#include "base_presenter.h"
#include "dao_traits.h"

namespace domain
{
    class MissionService;
}

namespace presentation
{
    class VerticalProfilePresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        explicit VerticalProfilePresenter(domain::MissionService* service,
                                          QObject* parent = nullptr);

    public slots:
        void selectMission(const dao::MissionPtr& mission);
        void updateMission();
        void clearMission();

    protected:
        void connectView(QObject* view) override;

    private:
        domain::MissionService* m_service;
        dao::MissionPtr m_mission;
    };
}

#endif // VERTICAL_PROFILE_PRESENTER_H
