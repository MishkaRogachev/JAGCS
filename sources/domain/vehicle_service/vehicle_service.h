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
        explicit VehicleService(data_source::DbEntry* entry,
                                QObject* parent = nullptr);
        ~VehicleService() override;

        data_source::VehicleDescriptionPtrList vehicles() const;

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // VEHICLE_SERVICE_H
