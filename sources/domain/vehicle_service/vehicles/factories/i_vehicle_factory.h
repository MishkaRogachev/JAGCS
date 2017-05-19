#ifndef I_VEHICLE_FACTORY_H
#define I_VEHICLE_FACTORY_H

namespace domain
{
    class BaseVehicle;

    class IVehicleFactory
    {
    public:
        IVehicleFactory() {}
        virtual ~IVehicleFactory() {}

        virtual BaseVehicle* create() = 0;
    };
}

#endif // I_VEHICLE_FACTORY_H
