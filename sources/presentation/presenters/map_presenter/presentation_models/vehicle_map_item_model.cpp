#include "vehicle_map_item_model.h"

// Qt
#include <QMap>
#include <QUrl>
#include <QDebug>

using namespace presentation;

class VehicleMapItemModel::Impl
{
public:
    QList<domain::Vehicle*> vehicles;
    QMap<domain::Vehicle*, QVariantList> tracks; // TODO: Rammer-Duglas-Pecker polyline simplification
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

    domain::Vehicle* vehicle = d->vehicles.at(index.row());

    switch (role)
    {
    case PositionRole:
        return QVariant::fromValue(vehicle->navigation().position());
    case DirectionRole:
        return vehicle->attitude().yaw();
    case MarkRole:
        return QUrl("qrc:/indicators/plane_map_mark.svg");
        // TODO: vehicle mark
    case TrackRole:
        return d->tracks[vehicle];
    case HomePositionRole:
        return QVariant::fromValue(vehicle->homePosition());
    default:
        return QVariant();
    }
}

QModelIndex VehicleMapItemModel::vehicleIndex(domain::Vehicle* vehicle) const
{
    return this->index(d->vehicles.indexOf(vehicle));
}

void VehicleMapItemModel::addVehicle(domain::Vehicle* vehicle)
{
    this->beginInsertRows(QModelIndex(), this->rowCount(), this->rowCount());
    d->vehicles.append(vehicle);
    connect(vehicle, &domain::Vehicle::navigationChanged,
            this, &VehicleMapItemModel::onVehicleNavigationChanged);
    connect(vehicle, &domain::Vehicle::attitudeChanged,
            this, &VehicleMapItemModel::onVehicleAttitudeChanged);
    connect(vehicle, &domain::Vehicle::homePositionChanged,
            this, &VehicleMapItemModel::onVehicleHomePositionChanged);
    this->endInsertRows();
}

void VehicleMapItemModel::removeVehicle(domain::Vehicle* vehicle)
{
    int row = d->vehicles.indexOf(vehicle);
    if (row == -1) return;

    this->beginRemoveRows(QModelIndex(), row, row);
    d->vehicles.removeOne(vehicle);
    d->tracks.remove(vehicle);
    disconnect(vehicle, 0, this, 0);
    this->endRemoveRows();
}

void VehicleMapItemModel::onVehicleNavigationChanged()
{
    domain::Vehicle* vehicle = qobject_cast<domain::Vehicle*>(this->sender());
    QModelIndex index = this->vehicleIndex(vehicle);
    d->tracks[vehicle].append(QVariant::fromValue(
                                  vehicle->navigation().position()));
    if (index.isValid()) emit dataChanged(index, index, {
                                              PositionRole, TrackRole });
}

void VehicleMapItemModel::onVehicleAttitudeChanged()
{
    QModelIndex index = this->vehicleIndex(qobject_cast<domain::Vehicle*>(
                                               this->sender()));
    if (index.isValid()) emit dataChanged(index, index, { DirectionRole });
}

void VehicleMapItemModel::onVehicleHomePositionChanged()
{
    QModelIndex index = this->vehicleIndex(qobject_cast<domain::Vehicle*>(
                                               this->sender()));
    if (index.isValid()) emit dataChanged(index, index, { HomePositionRole });
}

QHash<int, QByteArray> VehicleMapItemModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[PositionRole] = "position";
    roles[DirectionRole] = "direction";
    roles[MarkRole] = "mark";
    roles[TrackRole] = "track";
    roles[HomePositionRole] = "homePosition";

    return roles;
}
