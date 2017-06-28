#ifndef HOME_PRESENTER_H
#define HOME_PRESENTER_H

#include "base_presenter.h"

// Qt
#include <QGeoCoordinate>

// Internal
#include "telemetry.h"

namespace presentation
{
    class HomePresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        explicit HomePresenter(domain::Telemetry* positionNode,
                               domain::Telemetry* homePositionNode,
                               QObject* parent = nullptr);

    public slots:
        void onPositionChanged(const domain::Telemetry::TelemetryMap& parameters);
        void onHomePositionChanged(const domain::Telemetry::TelemetryMap& parameters);

        void updateView();

    protected:
        void connectView(QObject* view) override;

    private:
        domain::Telemetry* m_positionNode;
        domain::Telemetry* m_homePositionNode;

        QGeoCoordinate m_position;
        QGeoCoordinate m_homePosition;
    };
}

#endif // HOME_PRESENTER_H
