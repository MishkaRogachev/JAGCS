#include "vehicle_map_item_model.h"

// Qt
#include <QMap>
#include <QUrl>
#include <QDebug>

// Internal
#include "db_facade.h"
#include "vehicle_description.h"

#include "telemetry_service.h"

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
                                         domain::TelemetryService* vehicleService,
                                         QObject* parent):
    QAbstractListModel(parent),
    d(new Impl())
{
    d->dbFacade = dbFacade;
    d->telemetryService = vehicleService;

    connect(dbFacade, &db::DbFacade::vehicleAdded, this,
            &VehicleMapItemModel::onVehicleAdded);
    connect(dbFacade, &db::DbFacade::vehicleRemoved, this,
            &VehicleMapItemModel::onVehicleRemoved);

    connect(vehicleService, &domain::TelemetryService::positionChanged,
            this, &VehicleMapItemModel::onPositionChanged);
    connect(vehicleService, &domain::TelemetryService::snsChanged,
            this, &VehicleMapItemModel::onSnsChanged);

    for (const db::VehicleDescriptionPtr& vehicle: dbFacade->vehicles())
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

    switch (role)
    {
    case PositionRole:
        return QVariant::fromValue(d->telemetryService->position(vehicleId).coordinate());
    case DirectionRole:
        return d->telemetryService->position(vehicleId).vector().z();
    case MarkRole:
        return QUrl("qrc:/indicators/plane_map_mark.svg"); // TODO: vehicle type
    case VehicleIdRole:
        return d->dbFacade->vehicle(vehicleId)->mavId();
    case TrackRole:
        return d->tracks[vehicleId];
    case HdopRadius:
        return d->telemetryService->sns(vehicleId).eph();
    default:
        return QVariant();
    }
}

void VehicleMapItemModel::onVehicleAdded(const db::VehicleDescriptionPtr& vehicle)
{
    this->beginInsertRows(QModelIndex(), this->rowCount(), this->rowCount());
    d->vehicleIds.append(vehicle->id());

    this->endInsertRows();
}

void VehicleMapItemModel::onVehicleRemoved(const db::VehicleDescriptionPtr& vehicle)
{
    int row = d->vehicleIds.indexOf(vehicle->id());
    if (row == -1) return;

    this->beginRemoveRows(QModelIndex(), row, row);
    d->vehicleIds.removeOne(vehicle->id());
    d->tracks.remove(vehicle->id());

    this->endRemoveRows();
}

void VehicleMapItemModel::onPositionChanged(int vehicleId, const domain::Position& position)
{
    d->tracks[vehicleId].append(QVariant::fromValue(position.coordinate()));

    QModelIndex index = this->vehicleIndex(vehicleId);
    emit dataChanged(index, index, { PositionRole, DirectionRole, TrackRole });
}

void VehicleMapItemModel::onSnsChanged(int vehicleId, const domain::Sns& sns)
{
    Q_UNUSED(sns)

    QModelIndex index = this->vehicleIndex(vehicleId);
    emit dataChanged(index, index, { HdopRadius });
}

QHash<int, QByteArray> VehicleMapItemModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[PositionRole] = "position";
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
