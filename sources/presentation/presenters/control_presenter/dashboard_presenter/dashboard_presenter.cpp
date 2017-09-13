#include "dashboard_presenter.h"

// Qt
#include <QVariant>
#include <QMultiMap>

// Internal
#include "service_registry.h"
#include "vehicle_service.h"
#include "vehicle.h"

#include "telemetry.h"

using namespace presentation;

class DashboardPresenter::Impl
{
public:
    QMap<int, QString> instruments;
    QMultiMap<QString, BaseInstrumentPresenter*> instrumentPresenters;

   int vehicleId = -1;
};

DashboardPresenter::DashboardPresenter(int vehicleId, QObject* parent):
    BasePresenter(parent),
    d(new Impl())
{
    d->vehicleId = vehicleId;

    connect(domain::ServiceRegistry::vehicleService(), &domain::VehicleService::vehicleChanged,
            this, [this](const dao::VehiclePtr& vehicle) {
        if (d->vehicleId == vehicle->id()) this->updateVehicleIsOnline();
    });
}

DashboardPresenter::~DashboardPresenter()
{
    this->setViewProperty(PROPERTY(instruments), QStringList());
}

void DashboardPresenter::addInstrument(const QString& instrument, int priority)
{
    d->instruments[priority] = instrument;
}

void DashboardPresenter::addInstrumentPresenter(const QString& instrument, BaseInstrumentPresenter* presenter)
{
    d->instrumentPresenters.insertMulti(instrument, presenter);
}

void DashboardPresenter::connectView(QObject* view)
{
    connect(view, SIGNAL(instrumentAdded(QString, QObject*)),
            this, SLOT(onInstrumentAdded(QString, QObject*)));

    QStringList instruments = d->instruments.values();
    this->setViewProperty(PROPERTY(instruments), instruments);
    this->updateVehicleIsOnline();
}

void DashboardPresenter::onInstrumentAdded(const QString& key, QObject* view)
{
    for (BaseInstrumentPresenter* instrument: d->instrumentPresenters.values(key))
    {
        instrument->addInstrumentView(view);
    }
}

void DashboardPresenter::updateVehicleIsOnline()
{
    dao::VehiclePtr vehicle = domain::ServiceRegistry::vehicleService()->vehicle(d->vehicleId);
    if (vehicle) this->setViewProperty(PROPERTY(online), vehicle->isOnline());
}
