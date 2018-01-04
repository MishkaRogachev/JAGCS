#include "displays_model.h"

// Qt
#include <QDebug>

// Internal
#include "vehicle.h"

#include "dashboard_presenter.h"

using namespace presentation;

DisplaysModel::DisplaysModel(QObject* parent):
    QAbstractListModel(parent)
{}

int DisplaysModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)

    if (m_selectedVehicle) return 1;

    return m_vehicles.count();
}

QVariant DisplaysModel::data(const QModelIndex& index, int role) const
{
    dao::VehiclePtr vehicle;

    if (m_selectedVehicle)
    {
        vehicle = m_selectedVehicle;
    }
    else
    {
        if (m_vehicles.count() > index.row()) vehicle = m_vehicles.at(index.row());
        if (vehicle.isNull()) return QVariant();
    }

    switch (role)
    {
        case DisplayRole:
            if (m_selectedVehicle.isNull()) return DashboardPresenter::ShortVehicleDisplay;

            // TODO: displays for other vehicles
            return DashboardPresenter::FixedWingVehicleDisplay;
        case VehicleIdRole:
            return vehicle->id();
        default:
            return QVariant();
    }
}

void DisplaysModel::addVehicle(const dao::VehiclePtr& vehicle)
{
    this->beginInsertRows(QModelIndex(), this->rowCount(), this->rowCount());
    m_vehicles.append(vehicle);
    this->endInsertRows();
}

void DisplaysModel::removeVehicle(const dao::VehiclePtr& vehicle)
{
    int row = m_vehicles.indexOf(vehicle);

    this->beginRemoveRows(QModelIndex(), row, row);
    m_vehicles.removeOne(vehicle);
    this->endRemoveRows();
}

QHash<int, QByteArray> DisplaysModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[DisplayRole] = "display";
    roles[VehicleIdRole] = "vehicleId";

    return roles;
}
