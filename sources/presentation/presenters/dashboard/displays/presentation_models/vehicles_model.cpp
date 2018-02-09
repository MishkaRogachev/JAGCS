#include "vehicles_model.h"

// Qt
#include <QDebug>

// Internal
#include "vehicle.h"

#include "dashboard_presenter.h"

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
    if (index.row() >= m_vehicles.count()) return QVariant();

    dao::VehiclePtr vehicle = m_vehicles.at(index.row());

    switch (role)
    {
        case VehicleTypeRole:
            return vehicle->type();
        case VehicleIdRole:
            return vehicle->id();
        default:
            return QVariant();
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

    roles[VehicleTypeRole] = "vehicleType";
    roles[VehicleIdRole] = "vehicleId";

    return roles;
}
