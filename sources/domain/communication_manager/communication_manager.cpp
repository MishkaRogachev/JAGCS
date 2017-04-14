#include "communication_manager.h"

// Qt
#include <QMap>
#include <QDebug>

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

    AbstractLink* createLinkFromDescription(const LinkDescriptionPtr& description)
    {
        DescriptionLinkFactory factory(description);
        AbstractLink* link = factory.create();
        if (!link) return nullptr;

        descriptedLinks[description] = link;
        communicator->addLink(link);

        if (description->isAutoConnect()) link->connectLink();

        return link;
    }

    void updateLinkFromDescription(AbstractLink* link,
                                   const LinkDescriptionPtr& description)
    {
        DescriptionLinkFactory factory(description);
        factory.update(link);
    }
};

CommunicationManager::CommunicationManager(ICommunicatorFactory* commFactory,
                                           DbEntry* entry,
                                           QObject* parent):
    QObject(parent),
    d(new Impl())
{
    d->communicator = commFactory->create();
    d->entry = entry;

    for (const LinkDescriptionPtr& description: d->entry->loadLinks())
    {
        d->createLinkFromDescription(description)->setParent(this);
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

void CommunicationManager::saveLink(const LinkDescriptionPtr& description)
{
    AbstractLink* link;

    if (d->descriptedLinks.contains(description))
    {
        link = d->descriptedLinks[description];
        d->updateLinkFromDescription(link, description);
    }
    else
    {
        link = d->createLinkFromDescription(description);
        link->setParent(this);

        d->descriptedLinks[description] = link;
        d->communicator->addLink(link);

        emit linksChanged(this->links());
    }

    if (description->isAutoConnect() != link->isConnected())
    {
        link->setConnected(description->isAutoConnect());
        description->setAutoConnect(link->isConnected());
    }

    emit linkChanged(description);

    d->entry->save(description);
}

void CommunicationManager::removeLink(const LinkDescriptionPtr& description)
{
    AbstractLink* link = d->descriptedLinks.take(description);
    d->communicator->removeLink(link);
    delete link;

    emit linksChanged(this->links());

    d->entry->remove(description);
}
