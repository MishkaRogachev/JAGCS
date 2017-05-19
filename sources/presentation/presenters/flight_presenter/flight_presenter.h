#ifndef FLIGHT_PRESENTER_H
#define FLIGHT_PRESENTER_H

// Internal
#include "base_presenter.h"

namespace domain
{
    class DomainEntry;
}

namespace presentation
{
    class FlightPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        explicit FlightPresenter(domain::DomainEntry* entry, QObject* object);
        ~FlightPresenter() override;

    public slots:
        void updateVehicles();

    protected:
        void connectView(QObject* view) override;

    private slots:
        void onVehicleSelected(const QString& vehicleName);

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // FLIGHT_PRESENTER_H
