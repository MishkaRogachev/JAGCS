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
    int vehicleId = 0;
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
        if (vehicle->id() != d->vehicleId) return;

        this->setViewProperty(PROPERTY(vehicleName), vehicle->name());
        this->setViewProperty(PROPERTY(online), vehicle->isOnline());
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
    if (d->vehicleId == vehicleId) return;

    d->vehicleId = vehicleId;
    this->setNode(domain::ServiceRegistry::telemetryService()->vehicleNode(vehicleId));

    dao::VehiclePtr vehicle = d->vehicleService->vehicle(vehicleId);
    if (vehicle)
    {
        this->setViewProperty(PROPERTY(vehicleName), vehicle->name());
        this->setViewProperty(PROPERTY(online), vehicle->isOnline());
    }
}

void CommonVehicleDisplayPresenter::executeCommand(int commandType, const QVariant& args)
{
    dao::CommandPtr command = dao::CommandPtr::create();
    command->setType(dao::Command::CommandType(commandType));
    command->setArguments(args.toList());

    d->commands.append(command);
    d->commandService->executeCommand(d->vehicleId, command);
}

void CommonVehicleDisplayPresenter::rejectCommand(int commandType)
{
    d->commandService->cancelCommand(d->vehicleId, dao::Command::CommandType(commandType));
}

void CommonVehicleDisplayPresenter::connectNode(domain::Telemetry* node)
{
    this->chainNode(node->childNode(domain::Telemetry::Status),
                    std::bind(&CommonVehicleDisplayPresenter::updateStatus, this, std::placeholders::_1));
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
