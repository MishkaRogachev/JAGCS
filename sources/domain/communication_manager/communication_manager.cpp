#include "communication_manager.h"

// Qt
#include <QMap>

// Internal
#include "db_entry.h"
#include "link_description.h"

#include "abstract_communicator.h"
#include "abstract_link.h"
#include "description_link_factory.h"

#include "i_communicator_factory.h"

using namespace data_source;
using namespace domain;

class CommunicationManager::Impl
{
public:
    AbstractCommunicator* communicator;
    DbEntry* entry;

    QMap<data_source::LinkDescriptionPtr, AbstractLink*> descriptedLinks;
};

CommunicationManager::CommunicationManager(ICommunicatorFactory* commFactory,
                                           DbEntry* entry,
                                           QObject* parent):
    QObject(parent),
    d(new Impl())
{
    d->communicator = commFactory->create();
    d->entry = entry;

    LinkDescriptionPtrList descriptions = d->entry->readLinks();
    DescriptionLinkFactory linkFactory;

    for (const LinkDescriptionPtr& description: descriptions)
        this->addLink(description);
}

CommunicationManager::~CommunicationManager()
{}

void CommunicationManager::addLink(const LinkDescriptionPtr& description)
{
    DescriptionLinkFactory factory(description);
    AbstractLink* link = factory.create();
    if (!link) return;

    d->descriptedLinks[description] = link;
    d->communicator->addLink(link);
    link->setParent(this);

    if (description->isAutoConnect()) link->up();
}
