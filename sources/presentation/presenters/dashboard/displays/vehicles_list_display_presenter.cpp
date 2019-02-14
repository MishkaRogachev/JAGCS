#include "vehicles_list_display_presenter.h"

// Qt
#include <QSortFilterProxyModel>
#include <QGeoCoordinate>
#include <QVariant>
#include <QDebug>

// Internal
#include "vehicle.h"

#include "service_registry.h"
#include "vehicle_service.h"
#include "telemetry_service.h"
#include "telemetry_portion.h"

#include "vehicle_list_model.h"
#include "vehicle_list_sorting_model.h"

#include "command.h"

using namespace presentation;

class VehiclesListDisplayPresenter::Impl
{
public:
     domain::VehicleService* service = serviceRegistry->vehicleService();
     domain::TelemetryService* telemetry = serviceRegistry->telemetryService();

     VehicleListModel vehiclesModel;
     VehicleListSortingModel filterModel;
};

VehiclesListDisplayPresenter::VehiclesListDisplayPresenter(QObject* parent):
    CommonVehicleDisplayPresenter(parent),
    d(new Impl())
{
    d->vehiclesModel.setVehicles(d->service->vehicles());
    d->filterModel.setSourceModel(&d->vehiclesModel);

    connect(d->service, &domain::VehicleService::vehicleAdded,
            &d->vehiclesModel, &VehicleListModel::addVehicle);
    connect(d->service, &domain::VehicleService::vehicleRemoved,
            &d->vehiclesModel, &VehicleListModel::removeVehicle);
    connect(d->service, &domain::VehicleService::vehicleChanged,
            &d->vehiclesModel, &VehicleListModel::updateVehicle);
}

VehiclesListDisplayPresenter::~VehiclesListDisplayPresenter()
{}

void VehiclesListDisplayPresenter::setGlobalPoi(double latitude, double longitude, float altitude)
{
    using namespace domain;
    Telemetry* node = d->telemetry->swarmNode();
    TelemetryPortion portion(node);

    QGeoCoordinate coordinate(latitude, longitude, altitude);
    portion.setParameter({ Telemetry::Poi, Telemetry::Coordinate },
                         QVariant::fromValue(coordinate));
    portion.setParameter({ Telemetry::Poi, Telemetry::Group }, 0); // FIXME

    int poiN = node->childNode(Telemetry::Poi)->parameter(Telemetry::Number).toInt() + 1;
    portion.setParameter({ Telemetry::Poi, Telemetry::Number }, poiN);
    portion.setParameter({ Telemetry::Poi, Telemetry::Confirmed }, false);

    this->executeCommand(dto::Command::SetGlobalPoi, QVariant({ latitude, longitude, altitude, poiN }));
}

void VehiclesListDisplayPresenter::connectView(QObject* view)
{
    BasePresenter::connectView(view);

    this->setViewProperty(PROPERTY(vehicles), QVariant::fromValue(&d->filterModel));
}
