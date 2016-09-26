#include "abstract_communicator.h"

using namespace domain;

AbstractCommunicator::AbstractCommunicator(VehicleService* vehicleService,
                                           QObject* parent):
    QObject(parent),
    m_vehicleService(vehicleService)
{}
