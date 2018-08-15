#include "db_links_repository.h"

// Qt
#include <QDebug>

// Internal
#include "link_description.h"
#include "link_protocol.h"

#include "generic_repository.h"

using namespace data_source;

class DbLinksRepository::Impl
{
public:
    GenericRepository<dto::LinkDescription> descriptionRepository;
    GenericRepository<dto::LinkProtocol> protocolRepository;

    Impl():
        descriptionRepository("link_descriptions"),
        protocolRepository("link_protocols")
    {}

    void loadDescriptions(const QString& condition = QString(), bool reload = false)
    {
        for (int id: descriptionRepository.selectId(condition))
        {
            descriptionRepository.read(id, reload);
        }
    }

    void loadProtocols(const QString& condition = QString(), bool reload = false)
    {
        for (int id: protocolRepository.selectId(condition))
        {
            protocolRepository.read(id, reload);
        }
    }
};

DbLinksRepository::DbLinksRepository(QObject* parent):
    ILinksRepository(parent),
    d(new Impl())
{
    d->loadDescriptions();
    d->loadProtocols();
}

DbLinksRepository::~DbLinksRepository()
{}

dto::LinkDescriptionPtr DbLinksRepository::description(int id) const
{
    return d->descriptionRepository.read(id);
}

dto::LinkDescriptionPtrList DbLinksRepository::descriptions() const
{
    return d->descriptionRepository.loadedEntities();
}

dto::LinkProtocolPtr DbLinksRepository::protocol(int id) const
{
    return d->protocolRepository.read(id);
}

dto::LinkProtocolPtrList DbLinksRepository::protocols() const
{
    return d->protocolRepository.loadedEntities();
}

dto::LinkProtocolPtr DbLinksRepository::protocolByName(const QString& name) const
{
    for (int id: d->protocolRepository.selectId("WHERE name = " + name))
    {
        return this->protocol(id);
    }
    return dto::LinkProtocolPtr();
}

bool DbLinksRepository::save(const dto::LinkDescriptionPtr& description)
{
    bool isNew = description->id() == 0;
    if (!d->descriptionRepository.save(description)) return false;

    emit (isNew ? descriptionAdded(description) : descriptionChanged(description));
    return true;
}

bool DbLinksRepository::remove(const dto::LinkDescriptionPtr& description)
{
    if (d->descriptionRepository.remove(description))
    {
        emit descriptionRemoved(description);
        return true;
    }
    return false;
}

bool DbLinksRepository::save(const dto::LinkProtocolPtr& protocol)
{
    bool isNew = protocol->id() == 0;
    if (!d->protocolRepository.save(protocol)) return false;

    emit (isNew ? protocolAdded(protocol) : protocolChanged(protocol));
    return true;
}

bool DbLinksRepository::remove(const dto::LinkProtocolPtr& protocol)
{
    if (d->protocolRepository.remove(protocol))
    {
        emit protocolRemoved(protocol);
        return true;
    }
    return false;
}

