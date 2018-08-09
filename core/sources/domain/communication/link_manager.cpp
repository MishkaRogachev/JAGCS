#include "link_manager.h"

// Qt
#include <QDebug>

// Internal
#include "link_description.h"
#include "link_protocol.h"

#include "generic_repository.h"

#include "serial_ports_service.h"

using namespace domain;

class LinkManager::Impl
{
public:
    data_source::GenericRepository<dto::LinkDescription> descriptionRepository;
    data_source::GenericRepository<dto::LinkProtocol> protocolRepository;

    QMap<int, dto::LinkStatisticsPtr> linkStatistics;
    QMap<dto::LinkDescriptionPtr, QString> descriptedDevices;

    SerialPortService* serialPortService;

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

    for (const dto::LinkDescriptionPtr& description: this->descriptions())
    {
        QString device = description->parameter(dto::LinkDescription::Device).toString();
        if (description->type() == dto::LinkDescription::Serial && device.length() > 0)
        {
            d->serialPortService->holdDevice(device);
            d->descriptedDevices[description] = device;
        }
    }
}

LinkManager::~LinkManager()
{}

dto::LinkDescriptionPtr LinkManager::description(int id) const
{
    d->descriptionRepository.read(id);
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

    emit (isNew ? added(description) : changed(description));
}

bool LinkManager::remove(const dto::LinkDescriptionPtr& description)
{
    if (d->descriptionRepository.remove(description)) emit removed(description);
}

bool LinkManager::save(const dto::LinkProtocolPtr& protocol)
{
    bool isNew = protocol->id() == 0;
    if (!d->descriptionRepository.save(protocol)) return false;

    emit (isNew ? added(protocol) : changed(protocol));
}

bool LinkManager::remove(const dto::LinkProtocolPtr& protocol)
{
    if (d->protocolRepository.remove(protocol)) emit removed(protocol);
}

