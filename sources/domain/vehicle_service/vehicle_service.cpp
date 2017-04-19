#include "vehicle_service.h"

// Qt
#include <QMap>
#include <QDebug>

// Internal
#include "db_entry.h"
#include "link_description.h"

using namespace data_source;
using namespace domain;

class VehicleService::Impl
{
public:
    // QMap<VehicleDescriptionPtr, BaseVehicle*> vehicles;

};

VehicleService::VehicleService(QObject* parent):
    QObject(parent),
    d(new Impl())
{}

VehicleService::~VehicleService()
{}
