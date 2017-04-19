#include "description_vehicle_factory.h"

// Internal
#include "aerial_vehicle.h"

using namespace domain;

DescriptionVehicleFactory::DescriptionVehicleFactory(
        const data_source::VehicleDescriptionPtr& description):
    m_description(description)
{}

BaseVehicle* DescriptionVehicleFactory::create()
{
    if (m_description.isNull()) return nullptr;

    // TODO: vehicle type
    return new AerialVehicle(AerialVehicle::FixedWingAircraft);
}

data_source::VehicleDescriptionPtr DescriptionVehicleFactory::description() const
{
    return m_description;
}

void DescriptionVehicleFactory::setDescription(
        const data_source::VehicleDescriptionPtr& description)
{
    m_description = description;
}
