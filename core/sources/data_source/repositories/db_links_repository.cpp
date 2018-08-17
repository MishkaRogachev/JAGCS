#include "db_links_repository.h"

// Qt
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QDebug>

// Internal
#include "link_description.h"

#include "generic_repository.h"

namespace
{
    const QString tableName = "link_descriptions";
}

using namespace data_source;

class DbLinksRepository::Impl
{
public:
    GenericRepository<dto::LinkDescription> descriptionRepository;
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

DbLinksRepository::DbLinksRepository(const QSqlDatabase& db, QObject* parent):
    ILinksRepository(parent),
    d(new Impl())
{
    d->dbDriver = db.driver();
    Q_ASSERT(d->dbDriver);

    d->dbDriver->subscribeToNotification(::tableName);
    connect(db.driver(), QOverload<const QString &, QSqlDriver::NotificationSource,
            const QVariant &>::of(&QSqlDriver::notification),
            [this](const QString& name, QSqlDriver::NotificationSource, const QVariant& payload)
    {
        if (name != ::tableName) return;
        int id = payload.toInt();
        if (id < 1) return;

        qDebug() << id;

        if (d->descriptionRepository.contains(id))
        {
            qDebug() << "contains";
        }
        else
        {
            emit descriptionAdded(d->descriptionRepository.read(id));
        }
        qDebug() << "notify" << name << payload;
    });

    d->loadDescriptions();
}

DbLinksRepository::~DbLinksRepository()
{
    d->dbDriver->unsubscribeFromNotification(::tableName);
}

dto::LinkDescriptionPtr DbLinksRepository::description(int id) const
{
    return d->descriptionRepository.read(id);
}

dto::LinkDescriptionPtrList DbLinksRepository::descriptions() const
{
    return d->descriptionRepository.loadedEntities();
}

bool DbLinksRepository::save(const dto::LinkDescriptionPtr& description)
{
    return d->descriptionRepository.save(description);
}

bool DbLinksRepository::remove(const dto::LinkDescriptionPtr& description)
{
    return d->descriptionRepository.remove(description);
}

