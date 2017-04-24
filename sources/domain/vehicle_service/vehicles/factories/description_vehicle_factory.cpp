#include "description_vehicle_factory.h"

// Internal
#include "vehicle_description.h"
#include "aerial_vehicle.h"

using namespace domain;

DescriptionVehicleFactory::DescriptionVehicleFactory(
        const db::VehicleDescriptionPtr& description):
    m_description(description)
{}

BaseVehicle* DescriptionVehicleFactory::create()
{
    if (m_description.isNull()) return nullptr;

    // TODO: vehicle type
    return new AerialVehicle(m_description->mavId(),
                             AerialVehicle::FixedWingAircraft);
}

db::VehicleDescriptionPtr DescriptionVehicleFactory::description() const
{
    return m_description;
}

void DescriptionVehicleFactory::setDescription(
        const db::VehicleDescriptionPtr& description)
{
    m_description = description;
}
