#include "vehicles_model.h"

// Qt
#include <QDebug>

// Internal
#include "vehicle.h"

using namespace presentation;

VehiclesModel::VehiclesModel(QObject* parent):
    QAbstractListModel(parent)
{}

int VehiclesModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)

    return m_vehicles.count();
}

QVariant VehiclesModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid() || index.row() >= m_vehicles.count()) return QVariant();

    dao::VehiclePtr vehicle = m_vehicles.at(index.row());

    switch (role)
    {
    case VehicleIdRole: return vehicle->id();
    case VehicleTypeRole: return vehicle->type();
    case VehicleNameRole: return vehicle->name();
    case VehicleOnlineRole: return vehicle->isOnline();
    default: return QVariant();
    }
}

void VehiclesModel::setVehicles(const dao::VehiclePtrList& vehicles)
{
    this->beginResetModel();

    m_vehicles = vehicles;

    this->endResetModel();
}

void VehiclesModel::addVehicle(const dao::VehiclePtr& vehicle)
{
    this->beginInsertRows(QModelIndex(), this->rowCount(), this->rowCount());
    m_vehicles.append(vehicle);
    this->endInsertRows();
}

void VehiclesModel::updateVehicle(const dao::VehiclePtr& vehicle)
{
    QModelIndex index = this->index(m_vehicles.indexOf(vehicle));
    if (!index.isValid()) return;

    emit dataChanged(index, index, { VehicleTypeRole, VehicleNameRole, VehicleOnlineRole });
}

void VehiclesModel::removeVehicle(const dao::VehiclePtr& vehicle)
{
    int row = m_vehicles.indexOf(vehicle);

    this->beginRemoveRows(QModelIndex(), row, row);
    m_vehicles.removeOne(vehicle);
    this->endRemoveRows();
}

QHash<int, QByteArray> VehiclesModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[VehicleIdRole] = "vehicleId";
    roles[VehicleTypeRole] = "vehicleType";
    roles[VehicleNameRole] = "vehicleName";
    roles[VehicleOnlineRole] = "vehicleOnline";

    return roles;
}
