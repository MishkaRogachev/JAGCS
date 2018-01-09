#include "common_vehicle_display_presenter.h"

// Qt
#include <QVariant>
#include <QDebug>

// Internal
#include "vehicle.h"
#include "command.h"

#include "service_registry.h"
#include "vehicle_service.h"
#include "command_service.h"
#include "telemetry_service.h"

#include "modes.h"

using namespace presentation;

class CommonVehicleDisplayPresenter::Impl
{
public:
    dao::VehiclePtr vehicle;
    QList<dao::CommandPtr> commands;

    domain::VehicleService* vehicleService = domain::ServiceRegistry::vehicleService();
    domain::CommandService* commandService = domain::ServiceRegistry::commandService();
};

CommonVehicleDisplayPresenter::CommonVehicleDisplayPresenter(QObject* parent):
    AbstractTelemetryPresenter(parent),
    d(new Impl())
{
    connect(d->vehicleService, &domain::VehicleService::vehicleChanged,
            this, [this](const dao::VehiclePtr& vehicle) {
        if (vehicle == d->vehicle) this->updateVehicle();
    });

    connect(d->commandService, &domain::CommandService::commandChanged,
            this, [this](const dao::CommandPtr& command) {
        if (!d->commands.contains(command)) return;

        this->invokeViewMethod(PROPERTY(updateCommandStatus), command->type(), command->status());
        if (command->isFinished()) d->commands.removeOne(command);
    });
}

CommonVehicleDisplayPresenter::~CommonVehicleDisplayPresenter()
{}

void CommonVehicleDisplayPresenter::setVehicle(int vehicleId)
{
    if (d->vehicle && d->vehicle->id() == vehicleId) return;

    d->vehicle = d->vehicleService->vehicle(vehicleId);
    this->updateVehicle();

    this->setNode(domain::ServiceRegistry::telemetryService()->vehicleNode(vehicleId));
}

void CommonVehicleDisplayPresenter::updateVehicle()
{
    if (d->vehicle)
    {
        this->setViewProperty(PROPERTY(vehicleName), d->vehicle->name());
        this->setViewProperty(PROPERTY(vehicleType), d->vehicle->type());
        this->setViewProperty(PROPERTY(online), d->vehicle->isOnline());
    }
    else
    {
        this->setViewProperty(PROPERTY(vehicleName), QString());
        this->setViewProperty(PROPERTY(vehicleType), dao::Vehicle::UnknownType);
        this->setViewProperty(PROPERTY(online), false);
    }
}

void CommonVehicleDisplayPresenter::executeCommand(int commandType, const QVariant& args)
{
    if (d->vehicle.isNull()) return;

    dao::CommandPtr command = dao::CommandPtr::create();
    command->setType(dao::Command::CommandType(commandType));
    command->setArguments(args.toList());

    d->commands.append(command);
    d->commandService->executeCommand(d->vehicle->id(), command);
}

void CommonVehicleDisplayPresenter::rejectCommand(int commandType)
{
    if (d->vehicle.isNull()) return;

    d->commandService->cancelCommand(d->vehicle->id(), dao::Command::CommandType(commandType));
}

void CommonVehicleDisplayPresenter::connectNode(domain::Telemetry* node)
{
    this->chainNode(node->childNode(domain::Telemetry::Status),
                    std::bind(&CommonVehicleDisplayPresenter::updateStatus,
                              this, std::placeholders::_1));
}

void CommonVehicleDisplayPresenter::updateStatus(const domain::Telemetry::TelemetryMap& parameters)
{
    this->setViewProperty(PROPERTY(armed), parameters.value(domain::Telemetry::Armed));
    this->setViewProperty(PROPERTY(guided), parameters.value(domain::Telemetry::Guided));
    this->setViewProperty(PROPERTY(mode), parameters.value(domain::Telemetry::Mode));

    QVariantList modes;
    for (auto item: parameters.value(domain::Telemetry::AvailableModes).value<
         QList<domain::Mode> >())
    {
        if (item == domain::Mode::Return) continue; // special button for return

        modes.append(QVariant::fromValue(item));
    }
    this->setViewProperty(PROPERTY(availableModes), modes);
}
