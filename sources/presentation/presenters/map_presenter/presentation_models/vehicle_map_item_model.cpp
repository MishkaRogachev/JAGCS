#include "vehicle_map_item_model.h"

// Qt
#include <QMap>
#include <QUrl>
#include <QDebug>

// Internal
#include "aerial_vehicle.h"

using namespace presentation;

class VehicleMapItemModel::Impl
{
public:
    QList<domain::BaseVehicle*> vehicles;
    QMap<domain::BaseVehicle*, QVariantList> tracks;
    // TODO: Rammer-Duglas-Pecker polyline simplification

    QUrl vehicleTypeToMark(int type)
    {
        switch (type)
        { // TODO: vehicle marks
        case domain::AerialVehicle::FixedWingAircraft:
            return QUrl("qrc:/indicators/plane_map_mark.svg");
        case domain::AbstractVehicle::UnknownType:
        default:
            return QUrl("qrc:/indicators/unknown_mark.svg");
        }
    }

    // TODO: vehicle State To Color
    /*Boot,
    Calibrating,
    Standby,
    Active,
    Critical,
    Emergency,
    PowerOff*/
};

VehicleMapItemModel::VehicleMapItemModel(QObject* parent):
    QAbstractListModel(parent),
    d(new Impl())
{}

VehicleMapItemModel::~VehicleMapItemModel()
{
    delete d;
}

int VehicleMapItemModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return d->vehicles.count();
}

QVariant VehicleMapItemModel::data(const QModelIndex& index, int role) const
{
    if (index.row() < 0 || index.row() >= d->vehicles.count()) return QVariant();

    auto vehicle = d->vehicles.at(index.row());

    switch (role)
    {
    case PositionRole:
        return QVariant::fromValue(vehicle->position().coordinate());
    case DirectionRole:
        return vehicle->attitude().yaw();
    case MarkRole:
        return d->vehicleTypeToMark(vehicle->type());
    case VehicleIdRole:
        return vehicle->vehicleId();
    case TrackRole:
        return d->tracks[vehicle];
    case HdopRadius:
        return vehicle->gps().eph();
    default:
        return QVariant();
    }
}

void VehicleMapItemModel::addVehicle(domain::BaseVehicle* vehicle)
{
    this->beginInsertRows(QModelIndex(), this->rowCount(), this->rowCount());
    d->vehicles.append(vehicle);

    connect(vehicle, &domain::BaseVehicle::stateChanged,
            this, &VehicleMapItemModel::onVehicleStateChanged);
    connect(vehicle, &domain::BaseVehicle::attitudeChanged,
            this, &VehicleMapItemModel::onVehicleAttitudeChanged);
    connect(vehicle, &domain::BaseVehicle::positionChanged,
            this, &VehicleMapItemModel::onVehiclePositionChanged);
    connect(vehicle, &domain::BaseVehicle::gpsChanged,
            this, &VehicleMapItemModel::onVehicleGpsChanged);

    this->endInsertRows();
}

void VehicleMapItemModel::removeVehicle(domain::BaseVehicle* vehicle)
{
    int row = d->vehicles.indexOf(vehicle);
    if (row == -1) return;

    this->beginRemoveRows(QModelIndex(), row, row);
    d->vehicles.removeOne(vehicle);
    d->tracks.remove(vehicle);

    disconnect(vehicle, 0, this, 0);

    this->endRemoveRows();
}

void VehicleMapItemModel::onVehicleStateChanged()
{
    // TODO: handle state
}

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

QModelIndex VehicleMapItemModel::vehicleIndex(domain::BaseVehicle* vehicle) const
{
    return this->index(d->vehicles.indexOf(vehicle));
}
