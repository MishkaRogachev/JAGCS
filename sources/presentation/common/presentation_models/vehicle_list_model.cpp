#include "vehicle_list_model.h"

// Qt
#include <QDebug>

// Internal
#include "vehicle.h"

using namespace presentation;

VehicleListModel::VehicleListModel(QObject* parent):
    QAbstractListModel(parent)
{}

int VehicleListModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)

    return m_vehicles.count();
}

QVariant VehicleListModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid() || index.row() >= m_vehicles.count()) return QVariant();

    dto::VehiclePtr vehicle = m_vehicles.at(index.row());

    switch (role)
    {
    case VehicleIdRole: return vehicle->id();
    case VehicleTypeRole: return vehicle->type();
    case VehicleNameRole: return vehicle->name();
    case VehicleOnlineRole: return vehicle->isOnline();
    default: return QVariant();
    }
}

void VehicleListModel::setVehicles(const dto::VehiclePtrList& vehicles)
{
    this->beginResetModel();

    m_vehicles = vehicles;

    this->endResetModel();
}

void VehicleListModel::addVehicle(const dto::VehiclePtr& vehicle)
{
    this->beginInsertRows(QModelIndex(), this->rowCount(), this->rowCount());
    m_vehicles.append(vehicle);
    this->endInsertRows();
}

void VehicleListModel::updateVehicle(const dto::VehiclePtr& vehicle)
{
    QModelIndex index = this->index(m_vehicles.indexOf(vehicle));
    if (!index.isValid()) return;

    emit dataChanged(index, index, { VehicleTypeRole, VehicleNameRole, VehicleOnlineRole });
}

void VehicleListModel::removeVehicle(const dto::VehiclePtr& vehicle)
{
    int row = m_vehicles.indexOf(vehicle);
    if (row == -1) return;

    this->beginRemoveRows(QModelIndex(), row, row);
    m_vehicles.removeOne(vehicle);
    this->endRemoveRows();
}

QHash<int, QByteArray> VehicleListModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[VehicleIdRole] = "vehicleId";
    roles[VehicleTypeRole] = "vehicleType";
    roles[VehicleNameRole] = "vehicleName";
    roles[VehicleOnlineRole] = "vehicleOnline";

    return roles;
}
