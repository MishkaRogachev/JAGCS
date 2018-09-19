#ifndef DB_LINK_REPOSITORY_H
#define DB_LINK_REPOSITORY_H

// Internal
#include "i_link_repository.h"
#include "i_db_provider.h"

namespace data_source
{
    class DbLinkRepository: public ILinkRepository
    {
        Q_OBJECT

    public:
        DbLinkRepository(IDbProvider* provider, QObject* parent = nullptr);
        ~DbLinkRepository() override;

        LinkDescriptionPtr description(int id) const override;
        LinkDescriptionPtrList descriptions() const override;

    public slots:
        bool save(const LinkDescriptionPtr& description) override;
        bool remove(const LinkDescriptionPtr& description) override;

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // DB_LINK_REPOSITORY_H
