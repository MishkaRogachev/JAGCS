#include "vehicle_map_item_model.h"

// Qt
#include <QMap>
#include <QUrl>
#include <QDebug>

// Internal
#include "db_facade.h"
#include "vehicle.h"

#include "telemetry_service.h"
#include "telemetry.h"

using namespace presentation;

class VehicleMapItemModel::Impl
{
public:
    db::DbFacade* dbFacade;
    domain::TelemetryService* telemetryService;

    QList<int> vehicleIds;
    QMap<int, QVariantList> tracks;
    // TODO: Rammer-Duglas-Pecker polyline simplification, track from telemetry
};

VehicleMapItemModel::VehicleMapItemModel(db::DbFacade* dbFacade,
                                         domain::TelemetryService* telemetryService,
                                         QObject* parent):
    QAbstractListModel(parent),
    d(new Impl())
{
    d->dbFacade = dbFacade;
    d->telemetryService = telemetryService;

    connect(dbFacade, &db::DbFacade::vehicleAdded, this,
            &VehicleMapItemModel::onVehicleAdded);
    connect(dbFacade, &db::DbFacade::vehicleRemoved, this,
            &VehicleMapItemModel::onVehicleRemoved);

    for (const db::VehiclePtr& vehicle: dbFacade->vehicles())
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

    domain::Telemetry* node = d->telemetryService->node(vehicleId);
    if (!node) return QVariant();

    switch (role)
    {
    case CoordinateRole:
        return node->childNode(domain::Telemetry::Position)->parameter(domain::Telemetry::Coordinate);
    case DirectionRole:
        return node->childNode(domain::Telemetry::Compass)->parameter(domain::Telemetry::Heading);
    case MarkRole:
        return QUrl("qrc:/indicators/plane_map_mark.svg"); // TODO: vehicle type
    case VehicleIdRole:
        return d->dbFacade->vehicle(vehicleId)->mavId();
    case TrackRole:
        return d->tracks[vehicleId];
    case HdopRadius:
        return node->childNode(domain::Telemetry::Satellite)->parameter(domain::Telemetry::Eph);
    default:
        return QVariant();
    }
}

void VehicleMapItemModel::onVehicleAdded(const db::VehiclePtr& vehicle)
{
    int vehicleId = vehicle->id();
    this->beginInsertRows(QModelIndex(), this->rowCount(), this->rowCount());
    d->vehicleIds.append(vehicleId);

    domain::Telemetry* node = d->telemetryService->node(vehicle->id());

    connect(node->childNode(domain::Telemetry::Position), &domain::Telemetry::parametersChanged,
            this, [this, vehicleId](const domain::Telemetry::TelemetryMap& parameters) {
        this->onPositionParametersChanged(vehicleId, parameters);
    });

    connect(node->childNode(domain::Telemetry::Compass), &domain::Telemetry::parametersChanged,
            this, [this, vehicleId](const domain::Telemetry::TelemetryMap& parameters) {
        this->onCompassParametersChanged(vehicleId, parameters);
    });

    connect(node->childNode(domain::Telemetry::Satellite), &domain::Telemetry::parametersChanged,
            this, [this, vehicleId](const domain::Telemetry::TelemetryMap& parameters) {
        this->onSatelliteParametersChanged(vehicleId, parameters);
    });

    this->endInsertRows();
}

void VehicleMapItemModel::onVehicleRemoved(const db::VehiclePtr& vehicle)
{
    int row = d->vehicleIds.indexOf(vehicle->id());
    if (row == -1) return;

    domain::Telemetry* node = d->telemetryService->node(vehicle->id());
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
