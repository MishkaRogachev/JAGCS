#ifndef VEHICLE_SERVICE_H
#define VEHICLE_SERVICE_H

// Qt
#include <QObject>

// Internal
#include "db_traits.h"

namespace data_source
{
    class DbEntry;
}

namespace domain
{
    class VehicleService: public QObject
    {
        Q_OBJECT

    public:
        explicit VehicleService(QObject* parent = nullptr);
        ~VehicleService() override;

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // VEHICLE_SERVICE_H
