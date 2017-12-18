#include "vehicle_display_model.h"

// Qt
#include <QDebug>

// Internal
#include "vehicle.h"

#include "dashboard_presenter.h"

using namespace presentation;

namespace
{
    QVariantList instruments =
    {
        DashboardPresenter::SatelliteDispaly,
        DashboardPresenter::FlightDisplay,
        DashboardPresenter::NavigationDisplay,
        DashboardPresenter::ControlDisplay,
        DashboardPresenter::MissionDisplay
    };
}

VehicleDisplayModel::VehicleDisplayModel(const dao::VehiclePtr& vehicle, QObject* parent):
    QAbstractListModel(parent),
    m_vehicle(vehicle)
{
    // TODO: handle instrument's change
}

int VehicleDisplayModel::rowCount(const QModelIndex& parent) const
{
    return ::instruments.count();
}

QVariant VehicleDisplayModel::data(const QModelIndex& index, int role) const
{
    switch (role) {
    case InstrumentRole:
        return ::instruments.at(index.row());
    case VehicleIdRole:
        return m_vehicle->id();
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> VehicleDisplayModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[InstrumentRole] = "instrument";
    roles[VehicleIdRole] = "vehicleId";

    return roles;
}
