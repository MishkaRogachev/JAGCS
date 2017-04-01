#include "communication_manager.h"

// Internal
#include "abstract_communicator.h"
#include "db_entry.h"
#include "link_description.h"

#include "i_communicator_factory.h"

using namespace data_source;
using namespace domain;

class CommunicationManager::Impl
{
public:
    AbstractCommunicator* communicator;
    DbEntry* entry;

    data_source::LinkDescriptionPtrList descriptions;
};

CommunicationManager::CommunicationManager(ICommunicatorFactory* factory,
                                           DbEntry* entry,
                                           QObject* parent):
    QObject(parent),
    d(new Impl())
{
    d->communicator = factory->create();
    d->entry = entry;

    d->descriptions = d->entry->readLinks();

    for (const LinkDescriptionPtr& description: d->descriptions)
    {
        // TODO: link from description
    }
}

CommunicationManager::~CommunicationManager()
{}

void CommunicationManager::addLink(const LinkDescription& description)
{
    d->communicator->addLink(description);
}
