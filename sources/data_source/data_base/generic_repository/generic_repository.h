#ifndef GENERIC_REPOSITORY_H
#define GENERIC_REPOSITORY_H

// Qt
#include <QSqlQuery>

namespace data_source
{
    class IdentityMap;

    template <class T>
    class GenericRepository
    {
    public:
        GenericRepository();
        virtual ~GenericRepository();

        T* read(int id, IdentityMap* iMap);
        bool insert(T* entity);
        bool update(T* entity);
        bool remove(T* entity);

        QList<T*> select(const QString& condition);
        QList<int> selectId(const QString& condition);

    protected:
        bool runQuerry();

    private:
        QSqlQuery m_query;
    };
}

#endif // GENERIC_REPOSITORY_H
