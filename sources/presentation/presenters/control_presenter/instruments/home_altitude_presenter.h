#ifndef HOME_ALTITUDE_PRESENTER_H
#define HOME_ALTITUDE_PRESENTER_H

#include "abstract_telemetry_presenter.h"

// Qt
#include <QGeoCoordinate>

// Internal
#include "telemetry.h"

namespace presentation
{
    class HomeAltitudePresenter: public AbstractTelemetryPresenter
    {
        Q_OBJECT

    public:
        explicit HomeAltitudePresenter(domain::Telemetry* node, QObject* parent = nullptr);

    public slots:
        void onParametersChanged(const domain::Telemetry::TelemetryMap& parameters) override;
    };
}

#endif // HOME_ALTITUDE_PRESENTER_H
