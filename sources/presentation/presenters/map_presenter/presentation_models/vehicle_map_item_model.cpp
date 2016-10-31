#include "vehicle_map_item_model.h"

// Qt
#include <QUrl>
#include <QDebug>

using namespace presentation;

VehicleMapItemModel::VehicleMapItemModel(QObject* parent):
    QAbstractListModel(parent)
{}

int VehicleMapItemModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return m_vehicles.count();
}

QVariant VehicleMapItemModel::data(const QModelIndex& index, int role) const
{
    if (index.row() < 0 || index.row() >= m_vehicles.count()) return QVariant();

    domain::Vehicle* vehicle = m_vehicles.at(index.row());

    // TODO: other roles
    switch (role)
    {
    case PositionRole:
        return QVariant::fromValue(vehicle->navigation().position());
    case DirectionRole:
        return vehicle->attitude().yaw();
    case MarkRole:
        return QUrl("qrc:/indicators/plane_map_mark.svg");
        // TODO: vehicle mark
    default:
        return QVariant();
    }
}

QModelIndex VehicleMapItemModel::vehicleIndex(domain::Vehicle* vehicle) const
{
    return this->index(m_vehicles.indexOf(vehicle));
}

void VehicleMapItemModel::addVehicle(domain::Vehicle* vehicle)
{
    this->beginInsertRows(QModelIndex(), this->rowCount(), this->rowCount());
    m_vehicles.append(vehicle);
    connect(vehicle, &domain::Vehicle::navigationChanged,
            this, &VehicleMapItemModel::onVehicleNavigationChanged);
    connect(vehicle, &domain::Vehicle::attitudeChanged,
            this, &VehicleMapItemModel::onVehicleAttitudeChanged);
    this->endInsertRows();
}

void VehicleMapItemModel::removeVehicle(domain::Vehicle* vehicle)
{
    int row = m_vehicles.indexOf(vehicle);
    if (row == -1) return;

    this->beginRemoveRows(QModelIndex(), row, row);
    m_vehicles.removeOne(vehicle);
    disconnect(vehicle, 0, this, 0);
    this->endRemoveRows();
}

void VehicleMapItemModel::onVehicleNavigationChanged()
{
    QModelIndex index = this->vehicleIndex(qobject_cast<domain::Vehicle*>(
                                               this->sender()));
    if (index.isValid()) emit dataChanged(index, index, { PositionRole });
}

void VehicleMapItemModel::onVehicleAttitudeChanged()
{
    QModelIndex index = this->vehicleIndex(qobject_cast<domain::Vehicle*>(
                                               this->sender()));
    if (index.isValid()) emit dataChanged(index, index, { DirectionRole });
}

QHash<int, QByteArray> VehicleMapItemModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[PositionRole] = "position";
    roles[DirectionRole] = "direction";
    roles[MarkRole] = "mark";

    return roles;
}
