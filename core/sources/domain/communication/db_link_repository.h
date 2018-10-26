#ifndef DB_LINK_REPOSITORY_H
#define DB_LINK_REPOSITORY_H

// Internal
#include "i_link_repository.h"
#include "i_db_provider.h"

namespace domain
{
    class DbLinkRepository: public ILinkRepository
    {
        Q_OBJECT

    public:
        DbLinkRepository(data_source::IDbProvider* provider, QObject* parent = nullptr);
        ~DbLinkRepository() override;

        LinkDescription* description(int id) const override;
        QList<LinkDescription*> descriptions() const override;

    public slots:
        bool save(const LinkDescription* description) override;
        bool remove(const LinkDescription* description) override;

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // DB_LINK_REPOSITORY_H
