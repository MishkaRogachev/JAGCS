#include "db_links_repository.h"

// Qt
#include <QDebug>

// Internal
#include "link_description.h"

#include "generic_repository.h"

using namespace data_source;

class DbLinksRepository::Impl
{
public:
    GenericRepository<dto::LinkDescription> descriptionRepository;

    Impl():
        descriptionRepository("link_descriptions")
    {}

    void loadDescriptions(const QString& condition = QString(), bool reload = false)
    {
        for (int id: descriptionRepository.selectId(condition))
        {
            descriptionRepository.read(id, reload);
        }
    }
};

DbLinksRepository::DbLinksRepository(QObject* parent):
    ILinksRepository(parent),
    d(new Impl())
{
    d->loadDescriptions();
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

