#ifndef GENERIC_REPOSITORY_H
#define GENERIC_REPOSITORY_H

// Qt
#include <QSqlQuery>
#include <QHash>
#include <QSharedPointer>

namespace data_source
{
    template <class T>
    class GenericRepository
    {
    public:
        GenericRepository();
        virtual ~GenericRepository();

        QSharedPointer<T> read(int id, bool reload = false);
        bool insert(const QSharedPointer<T>& entity);
        bool update(const QSharedPointer<T>& entity);
        bool remove(const QSharedPointer<T>& entity);

        bool save(const QSharedPointer<T>& entity);
        bool contains(int id);
        void unload(int id);

        QList<int> selectId(const QString& condition);

    protected:
        bool runQuerry();
        QStringList propertyNames(const QMetaObject& meta);

        void bindQuery(QSqlQuery& query,
                       const QMetaObject& meta,
                       T* entity);
        void updateFromQuery(const QSqlQuery& query,
                             const QMetaObject& meta,
                             T* entity);

    private:
        QSqlQuery m_query;
        QHash<int, QSharedPointer<T> > m_map;
    };
}

#endif // GENERIC_REPOSITORY_H
