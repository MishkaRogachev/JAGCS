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

//    connect(vehicle, &domain::BaseVehicle::stateChanged,
//            this, &VehicleMapItemModel::onVehicleStateChanged);
//    connect(vehicle, &domain::BaseVehicle::attitudeChanged,
//            this, &VehicleMapItemModel::onVehicleAttitudeChanged);
//    connect(vehicle, &domain::BaseVehicle::positionChanged,
//            this, &VehicleMapItemModel::onVehiclePositionChanged);
//    connect(vehicle, &domain::BaseVehicle::gpsChanged,
//            this, &VehicleMapItemModel::onVehicleGpsChanged);

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

    auto vehicle = d->vehicleIds.at(index.row());

    switch (role)
    {
/*    case PositionRole:
        return QVariant::fromValue(vehicle->position().coordinate());
    case DirectionRole:
        return vehicle->attitude().yaw();
    case MarkRole:
        return QUrl("qrc:/indicators/plane_map_mark.svg"); // TODO: vehicle type
    case VehicleIdRole:
        return 0; //TODO: vehicleId
    case TrackRole:
        return d->tracks[vehicle];
    case HdopRadius:
        return vehicle->gps().eph();*/
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

/*
void VehicleMapItemModel::onVehiclePositionChanged()
{
    auto vehicle = qobject_cast<domain::BaseVehicle*>(this->sender());
    QModelIndex index = this->vehicleIndex(vehicle);
    d->tracks[vehicle].append(QVariant::fromValue(
                                  vehicle->position().coordinate()));
    if (index.isValid()) emit dataChanged(index, index, {
                                              PositionRole, TrackRole });
}

void VehicleMapItemModel::onVehicleAttitudeChanged()
{
    QModelIndex index = this->vehicleIndex(qobject_cast<domain::BaseVehicle*>(
                                               this->sender()));
    if (index.isValid()) emit dataChanged(index, index, { DirectionRole });
}

void VehicleMapItemModel::onVehicleGpsChanged()
{
    QModelIndex index = this->vehicleIndex(qobject_cast<domain::BaseVehicle*>(
                                               this->sender()));
    if (index.isValid()) emit dataChanged(index, index, { HdopRadius });
}*/

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
