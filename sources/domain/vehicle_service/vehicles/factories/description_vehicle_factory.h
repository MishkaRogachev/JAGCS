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
                const data_source::VehicleDescriptionPtr& description =
                data_source::VehicleDescriptionPtr());

        BaseVehicle* create() override;

        data_source::VehicleDescriptionPtr description() const;
        void setDescription(const data_source::VehicleDescriptionPtr& description);

    private:
        data_source::VehicleDescriptionPtr m_description;
    };
}

#endif // DESCRIPTION_VEHICLE_FACTORY_H
