#ifndef VERTICAL_PROFILE_PRESENTER_H
#define VERTICAL_PROFILE_PRESENTER_H

// Internal
#include "base_presenter.h"
#include "dto_traits.h"

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
        explicit VerticalProfilePresenter(QObject* parent = nullptr);

    public slots:
        void selectMission(const dto::MissionPtr& mission);
        void updateMission();
        void clearMission();

    protected:
        void connectView(QObject* view) override;

    private:
        domain::MissionService* m_service;
        dto::MissionPtr m_mission;
    };
}

#endif // VERTICAL_PROFILE_PRESENTER_H
