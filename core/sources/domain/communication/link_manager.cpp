#include "link_manager.h"

// Qt
#include <QDebug>

// Internal
#include "link_description.h"
#include "link_protocol.h"

#include "generic_repository.h"

using namespace domain;

class LinkManager::Impl
{
public:
    data_source::GenericRepository<dto::LinkDescription> descriptionRepository;
    data_source::GenericRepository<dto::LinkProtocol> protocolRepository;

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

LinkManager::LinkManager(QObject* parent):
    QObject(parent),
    d(new Impl())
{
    d->loadDescriptions();
    d->loadProtocols();
}

LinkManager::~LinkManager()
{}

dto::LinkDescriptionPtr LinkManager::description(int id) const
{
    return d->descriptionRepository.read(id);
}

dto::LinkDescriptionPtrList LinkManager::descriptions() const
{
    return d->descriptionRepository.loadedEntities();
}

dto::LinkProtocolPtr LinkManager::protocol(int id) const
{
    return d->protocolRepository.read(id);
}

dto::LinkProtocolPtrList LinkManager::protocols() const
{
    return d->protocolRepository.loadedEntities();
}

bool LinkManager::save(const dto::LinkDescriptionPtr& description)
{
    bool isNew = description->id() == 0;
    if (!d->descriptionRepository.save(description)) return false;

    emit (isNew ? descriptionAdded(description) : descriptionChanged(description));
    return true;
}

bool LinkManager::remove(const dto::LinkDescriptionPtr& description)
{
    if (d->descriptionRepository.remove(description))
    {
        emit descriptionRemoved(description);
        return true;
    }
    return false;
}

bool LinkManager::save(const dto::LinkProtocolPtr& protocol)
{
    bool isNew = protocol->id() == 0;
    if (!d->protocolRepository.save(protocol)) return false;

    emit (isNew ? protocolAdded(protocol) : protocolChanged(protocol));
    return true;
}

bool LinkManager::remove(const dto::LinkProtocolPtr& protocol)
{
    if (d->protocolRepository.remove(protocol))
    {
        emit protocolRemoved(protocol);
        return true;
    }
    return false;
}

