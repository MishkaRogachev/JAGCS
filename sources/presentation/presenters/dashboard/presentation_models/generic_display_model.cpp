#include "generic_display_model.h"

// Qt
#include <QDebug>

// Internal
#include "vehicle.h"

#include "service_registry.h"
#include "vehicle_service.h"

#include "dashboard_presenter.h"

using namespace presentation;

class GenericDisplayModel::Impl
{
public:
    domain::VehicleService* service = domain::ServiceRegistry::vehicleService();
};

GenericDisplayModel::GenericDisplayModel(QObject* parent):
    AbstractDisplayModel(parent),
    d(new Impl())
{}

GenericDisplayModel::~GenericDisplayModel()
{}

int GenericDisplayModel::rowCount(const QModelIndex& parent) const
{
    return d->service->vehicles().count();
}

QVariant GenericDisplayModel::data(const QModelIndex& index, int role) const
{
    switch (role) {
    case InstrumentRole:
        return DashboardPresenter::VehicleDispaly;
    case VehicleIdRole:
        return d->service->vehicles().at(index.row())->id();
    default:
        return QVariant();
    }
}
