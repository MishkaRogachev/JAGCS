#ifndef LINK_MANAGER_H
#define LINK_MANAGER_H

// Internal
#include "i_links_repository.h"
#include "i_db_provider.h"

namespace data_source
{
    class DbLinksRepository: public ILinksRepository
    {
        Q_OBJECT

    public:
        DbLinksRepository(IDbProvider* provider, QObject* parent = nullptr);
        ~DbLinksRepository() override;

        dto::LinkDescriptionPtr description(int id) const override;
        dto::LinkDescriptionPtrList descriptions() const override;

    public slots:
        bool save(const dto::LinkDescriptionPtr& description) override;
        bool remove(const dto::LinkDescriptionPtr& description) override;

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // LINK_MANAGER_H
