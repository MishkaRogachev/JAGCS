#include "abstract_map_presenter.h"

// Qt
#include <QDebug>

// Internal
#include "service_registry.h"
#include "command_service.h"

using namespace presentation;

AbstractMapPresenter::AbstractMapPresenter(QObject* object):
    BasePresenter(object),
    m_commandService(serviceRegistry->commandService())
{}

void AbstractMapPresenter::navTo(int vehicleId, double latitude, double longitude, float altitude)
{
    dto::CommandPtr command = dto::CommandPtr::create();
    command->setType(dto::Command::NavTo);
    command->setArguments( { latitude, longitude, altitude} );

    m_commandService->executeCommand(vehicleId, command);
}
