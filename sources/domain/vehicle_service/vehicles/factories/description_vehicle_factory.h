#ifndef DESCRIPTION_VEHICLE_FACTORY_H
#define DESCRIPTION_VEHICLE_FACTORY_H

// Internal
#include "i_vehicle_factory.h"
#include "db_traits.h"

namespace domain
{
    class DescriptionVehicleFactory: public IVehicleFactory
    {
    public:
        DescriptionVehicleFactory(
                const db::VehicleDescriptionPtr& description =
                db::VehicleDescriptionPtr());

        BaseVehicle* create() override;

        db::VehicleDescriptionPtr description() const;
        void setDescription(const db::VehicleDescriptionPtr& description);

    private:
        db::VehicleDescriptionPtr m_description;
    };
}

#endif // DESCRIPTION_VEHICLE_FACTORY_H
