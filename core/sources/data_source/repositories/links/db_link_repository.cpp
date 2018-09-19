#include "db_link_repository.h"

// Qt
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QDebug>

// Internal
#include "link_description.h"

#include "generic_db_repository.h"

namespace
{
    const QString tableName = "link_descriptions";
}

using namespace data_source;

class DbLinkRepository::Impl
{
public:
    GenericDbRepository<LinkDescription> descriptionRepository;
    QSqlDriver* dbDriver;

    Impl():
        descriptionRepository(::tableName)
    {}

    void loadDescriptions(const QString& condition = QString(), bool reload = false)
    {
        for (int id: descriptionRepository.selectId(condition))
        {
            descriptionRepository.read(id, reload);
        }
    }
};

DbLinkRepository::DbLinkRepository(IDbProvider* provider, QObject* parent):
    ILinkRepository(parent),
    d(new Impl())
{
    d->dbDriver = provider->database().driver();
    Q_ASSERT(d->dbDriver);

    d->dbDriver->subscribeToNotification(::tableName);
    connect(d->dbDriver, QOverload<const QString &, QSqlDriver::NotificationSource,
            const QVariant &>::of(&QSqlDriver::notification),
            [this](const QString& name, QSqlDriver::NotificationSource, const QVariant& payload)
    {
        if (name != ::tableName) return;
        int id = payload.toInt();
        if (id < 1) return;

        bool contains = d->descriptionRepository.contains(id);
        LinkDescriptionPtr description = d->descriptionRepository.read(id);

        if (contains)
        {
            if (d->descriptionRepository.selectId().contains(id))
            {
                emit descriptionChanged(description);
            }
            else
            {
                emit descriptionRemoved(description);
                d->descriptionRepository.unload(id);
            }
        }
        else emit descriptionAdded(description);
    });

    d->loadDescriptions();
}

DbLinkRepository::~DbLinkRepository()
{
    d->dbDriver->unsubscribeFromNotification(::tableName);
}

LinkDescriptionPtr DbLinkRepository::description(int id) const
{
    return d->descriptionRepository.read(id);
}

LinkDescriptionPtrList DbLinkRepository::descriptions() const
{
    return d->descriptionRepository.loadedEntities();
}

bool DbLinkRepository::save(const LinkDescriptionPtr& description)
{
    return d->descriptionRepository.save(description);
}

bool DbLinkRepository::remove(const LinkDescriptionPtr& description)
{
    return d->descriptionRepository.remove(description);
}

