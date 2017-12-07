#ifndef NAVIGATION_DISPLAY_PRESENTER_H
#define NAVIGATION_DISPLAY_PRESENTER_H

// Internal
#include "abstract_instrument_presenter.h"

// Qt
#include <QGeoCoordinate>

namespace presentation
{
    class NavigationDisplayPresenter: public AbstractInstrumentPresenter
    {
        Q_OBJECT

    public:
        explicit NavigationDisplayPresenter(QObject* parent = nullptr);

    protected:
        void connectNode(domain::Telemetry* node) override;

    private slots:
        void updateStatus(const domain::Telemetry::TelemetryMap& parameters);
        void updateCompas(const domain::Telemetry::TelemetryMap& parameters);
        void updateSatellite(const domain::Telemetry::TelemetryMap& parameters);
        void updatePosition(const domain::Telemetry::TelemetryMap& parameters);
        void updateHome(const domain::Telemetry::TelemetryMap& parameters);
        void updateNavigator(const domain::Telemetry::TelemetryMap& parameters);
        void updateWind(const domain::Telemetry::TelemetryMap& parameters);

    private:
        void updateHoming();

        QGeoCoordinate m_position;
        QGeoCoordinate m_homePosition;
    };
}

#endif // NAVIGATION_DISPLAY_PRESENTER_H
