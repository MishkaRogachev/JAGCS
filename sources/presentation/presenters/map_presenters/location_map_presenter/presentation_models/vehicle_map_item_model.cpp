#include "vehicle_map_item_model.h"

// Qt
#include <QMap>
#include <QUrl>
#include <QDebug>

// Internal
#include "db_facade.h"
#include "vehicle.h"

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

    domain::TelemetryNode* node = d->telemetryService->node(vehicleId);
    if (!node) return QVariant();

    switch (role)
    {
    case CoordinateRole: return node->parameter(telemetry::coordinate);
    case DirectionRole: return node->parameter(telemetry::heading);
    case MarkRole: return QUrl("qrc:/indicators/plane_map_mark.svg"); // TODO: vehicle type
    case VehicleIdRole: return d->dbFacade->vehicle(vehicleId)->mavId();
    case TrackRole:
        return d->tracks[vehicleId];
    case HdopRadius:
        return node->childNode(telemetry::satellite)->parameter(telemetry::eph);
    default:
        return QVariant();
    }
}

void VehicleMapItemModel::onVehicleAdded(const db::VehiclePtr& vehicle)
{
    int vehicleId = vehicle->id();
    this->beginInsertRows(QModelIndex(), this->rowCount(), this->rowCount());
    d->vehicleIds.append(vehicleId);

    domain::TelemetryNode* node = d->telemetryService->node(vehicle->id());
    if (node) connect(node, &domain::TelemetryNode::parametersChanged, this,
                      [this, vehicleId](const QVariantMap& parameters) {
        if (parameters.contains(telemetry::coordinate))
        {
            d->tracks[vehicleId].append(parameters[telemetry::coordinate]);
        }
        this->onVehicleTelemetryChanged(vehicleId, parameters.keys());
    });

    this->endInsertRows();
}

void VehicleMapItemModel::onVehicleRemoved(const db::VehiclePtr& vehicle)
{
    int row = d->vehicleIds.indexOf(vehicle->id());
    if (row == -1) return;

    domain::TelemetryNode* node = d->telemetryService->node(vehicle->id());
    if (node) disconnect(node, 0, this, 0);

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

void VehicleMapItemModel::onVehicleTelemetryChanged(int vehicleId,
                                                    const QStringList& parameters)
{
    QModelIndex index = this->vehicleIndex(vehicleId);
    if (!index.isValid()) return;

    QVector<int> roles;

    if (parameters.contains(telemetry::coordinate)) roles.append({ CoordinateRole, TrackRole });
    if (parameters.endsWith(telemetry::heading)) roles.append(DirectionRole);
    if (parameters.endsWith(telemetry::eph)) roles.append(HdopRadius);

    emit dataChanged(index, index, roles);
}
