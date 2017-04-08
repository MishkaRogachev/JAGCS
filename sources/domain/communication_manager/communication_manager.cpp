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

    DescriptionLinkFactory factory; // TODO: link to description notify
    for (const LinkDescriptionPtr& description: d->entry->loadLinks())
    {
        AbstractLink* link = factory.create();
        if (!link) continue;

        d->descriptedLinks[description] = link;
        d->communicator->addLink(link);
        link->setParent(this);

        if (description->isAutoConnect()) link->up();
    }
}

CommunicationManager::~CommunicationManager()
{
    for (const LinkDescriptionPtr& description: d->descriptedLinks.keys())
    {
        d->entry->save(description);
    }
}

LinkDescriptionPtrList CommunicationManager::links() const
{
    return d->descriptedLinks.keys();
}

void CommunicationManager::addLink(const LinkDescriptionPtr& description)
{
    DescriptionLinkFactory factory(description);
    AbstractLink* link = factory.create();
    if (!link) return;

    d->descriptedLinks[description] = link;
    d->communicator->addLink(link);
    link->setParent(this);

    if (description->isAutoConnect()) link->up();

    d->entry->save(description);
}

void CommunicationManager::removeLink(const LinkDescriptionPtr& description)
{
    AbstractLink* link = d->descriptedLinks.take(description);
    d->communicator->removeLink(link);
    delete link;

    d->entry->remove(description);
}
