#include "vehicle_map_item_model.h"

// Qt
#include <QMap>
#include <QUrl>
#include <QGeoCoordinate>
#include <QDebug>

// Internal
#include "vehicle_service.h"
#include "vehicle.h"

#include "telemetry_service.h"
#include "telemetry.h"

#include "vehicle_type_mapper.h"

using namespace presentation;

class VehicleMapItemModel::Impl
{
public:
    domain::VehicleService* vehicleService;
    domain::TelemetryService* telemetryService;

    QList<int> vehicleIds;
    QMap<int, QVariantList> tracks;
    // TODO: Rammer-Duglas-Pecker polyline simplification, track from telemetry
};

VehicleMapItemModel::VehicleMapItemModel(domain::VehicleService* vehicleService,
                                         domain::TelemetryService* telemetryService,
                                         QObject* parent):
    QAbstractListModel(parent),
    d(new Impl())
{
    d->vehicleService = vehicleService;
    d->telemetryService = telemetryService;

    connect(vehicleService, &domain::VehicleService::vehicleAdded,
            this, &VehicleMapItemModel::onVehicleAdded);
    connect(vehicleService, &domain::VehicleService::vehicleRemoved,
            this, &VehicleMapItemModel::onVehicleRemoved);

    for (const dao::VehiclePtr& vehicle: vehicleService->vehicles())
    {
        this->onVehicleAdded(vehicle);
    }
}

VehicleMapItemModel::~VehicleMapItemModel()
{
    delete d;
}

int VehicleMapItemModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return d->vehicleIds.count();
}

QVariant VehicleMapItemModel::data(const QModelIndex& index, int role) const
{
    if (index.row() < 0 || index.row() >= d->vehicleIds.count()) return QVariant();

    int vehicleId = d->vehicleIds.at(index.row());

    domain::Telemetry* node = d->telemetryService->vehicleNode(vehicleId);
    dao::VehiclePtr vehicle = d->vehicleService->vehicle(vehicleId);
    if (!node || vehicle.isNull()) return QVariant();

    QVariant data;

    switch (role)
    {
    case CoordinateRole:
        data = node->childNode(domain::Telemetry::Position)->parameter(
                   domain::Telemetry::Coordinate);
        if (!data.isValid()) data = QVariant::fromValue(QGeoCoordinate());
        break;
    case DirectionRole:
        data = node->childNode(domain::Telemetry::Compass)->parameter(
                   domain::Telemetry::Heading);
        if (!data.isValid()) data = 0;
        break;
    case MarkRole:
        data = ::vehicleIcon(vehicle->type());
        break;
    case VehicleIdRole:
        data = vehicle->mavId();
        break;
    case TrackRole:
        data = d->tracks[vehicleId];
        break;
    case HdopRadius:
        data = node->childNode(domain::Telemetry::Satellite)->parameter(
                   domain::Telemetry::Eph);
        if (!data.isValid()) data = 0;
        break;
    case HomeCoordinateRole:
        data = node->childNode(domain::Telemetry::HomePosition)->parameter(
                   domain::Telemetry::Coordinate);
        if (!data.isValid()) data = QVariant::fromValue(QGeoCoordinate());
        break;
    }

    return data;
}

void VehicleMapItemModel::onVehicleAdded(const dao::VehiclePtr& vehicle)
{
    int vehicleId = vehicle->id();
    this->beginInsertRows(QModelIndex(), this->rowCount(), this->rowCount());
    d->vehicleIds.append(vehicleId);

    domain::Telemetry* node = d->telemetryService->vehicleNode(vehicle->id());

    connect(node->childNode(domain::Telemetry::Position),
            &domain::Telemetry::parametersChanged,
            this, [this, vehicleId](const domain::Telemetry::TelemetryMap& parameters) {
        this->onPositionParametersChanged(vehicleId, parameters);
    });

    connect(node->childNode(domain::Telemetry::Compass),
            &domain::Telemetry::parametersChanged,
            this, [this, vehicleId](const domain::Telemetry::TelemetryMap& parameters) {
        this->onCompassParametersChanged(vehicleId, parameters);
    });

    connect(node->childNode(domain::Telemetry::Satellite),
            &domain::Telemetry::parametersChanged,
            this, [this, vehicleId](const domain::Telemetry::TelemetryMap& parameters) {
        this->onSatelliteParametersChanged(vehicleId, parameters);
    });

    connect(node->childNode(domain::Telemetry::HomePosition),
            &domain::Telemetry::parametersChanged,
            this, [this, vehicleId](const domain::Telemetry::TelemetryMap& parameters) {
        this->onHomeParametersChanged(vehicleId, parameters);
    });

    this->endInsertRows();
}

void VehicleMapItemModel::onVehicleRemoved(const dao::VehiclePtr& vehicle)
{
    int row = d->vehicleIds.indexOf(vehicle->id());
    if (row == -1) return;

    domain::Telemetry* node = d->telemetryService->vehicleNode(vehicle->id());
    disconnect(node, 0, this, 0);

    this->beginRemoveRows(QModelIndex(), row, row);
    d->vehicleIds.removeOne(vehicle->id());
    d->tracks.remove(vehicle->id());

    this->endRemoveRows();
}

QHash<int, QByteArray> VehicleMapItemModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[CoordinateRole] = "position";
    roles[DirectionRole] = "direction";
    roles[MarkRole] = "mark";
    roles[VehicleIdRole] = "vehicleId";
    roles[TrackRole] = "track";
    roles[HdopRadius] = "hdopRadius";
    roles[HomeCoordinateRole] = "homePosition";

    return roles;
}

QModelIndex VehicleMapItemModel::vehicleIndex(int vehicleId) const
{
    return this->index(d->vehicleIds.indexOf(vehicleId));
}

void VehicleMapItemModel::onPositionParametersChanged(
        int vehicleId, const domain::Telemetry::TelemetryMap& parameters)
{
    QModelIndex index = this->vehicleIndex(vehicleId);
    if (!index.isValid()) return;

    if (parameters.contains(domain::Telemetry::Coordinate))
    {
        d->tracks[vehicleId].append(parameters[domain::Telemetry::Coordinate]);
    }

    emit dataChanged(index, index, { CoordinateRole });
}

void VehicleMapItemModel::onCompassParametersChanged(
        int vehicleId, const domain::Telemetry::TelemetryMap& parameters)
{
    Q_UNUSED(parameters)

    QModelIndex index = this->vehicleIndex(vehicleId);
    if (!index.isValid()) return;

    emit dataChanged(index, index, { DirectionRole });
}

void VehicleMapItemModel::onSatelliteParametersChanged(
        int vehicleId, const domain::Telemetry::TelemetryMap& parameters)
{
    Q_UNUSED(parameters)

    QModelIndex index = this->vehicleIndex(vehicleId);
    if (!index.isValid()) return;

    emit dataChanged(index, index, { HdopRadius });
}

void VehicleMapItemModel::onHomeParametersChanged(
        int vehicleId, const domain::Telemetry::TelemetryMap& parameters)
{
    Q_UNUSED(parameters)

    QModelIndex index = this->vehicleIndex(vehicleId);
    if (!index.isValid()) return;

    emit dataChanged(index, index, { HomeCoordinateRole });
}
