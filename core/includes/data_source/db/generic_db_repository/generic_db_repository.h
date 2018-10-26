#ifndef GENERIC_DB_REPOSITORY_H
#define GENERIC_DB_REPOSITORY_H

// Qt
#include <QSqlQuery>
#include <QHash>
#include <QSharedPointer>

namespace data_source
{
    template <class T>
    class GenericDbRepository
    {
    public:
        GenericDbRepository(const QString& tableName);
        virtual ~GenericDbRepository();

        QSharedPointer<T> read(int id, bool reload = false);
        bool insert(const QSharedPointer<T>& entity);
        bool update(const QSharedPointer<T>& entity);
        bool remove(const QSharedPointer<T>& entity);

        bool save(const QSharedPointer<T>& entity);
        bool contains(int id);
        void unload(int id);
        void clear();

        QList<int> selectId(const QString& condition = QString());

        QList<int> loadedIds() const;
        QList< QSharedPointer<T> > loadedEntities() const;

    protected:
        bool runQuerry();
        QStringList propertyNames(const QMetaObject& meta);

        void bindQuery(QSqlQuery& query, const QMetaObject& meta, T* entity);
        void updateFromQuery(const QSqlQuery& query, const QMetaObject& meta, T* entity);

    private:
        QSqlQuery m_query;
        const QString m_tableName;
        QStringList m_columnNames;
        QHash<int, QSharedPointer<T> > m_map;
    };
}

#include "generic_db_repository.hpp"

#endif // GENERIC_DB_REPOSITORY_H
