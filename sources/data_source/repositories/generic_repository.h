#ifndef GENERIC_REPOSITORY_H
#define GENERIC_REPOSITORY_H

// Qt
#include <QSqlQuery>

namespace data_source
{
    template <class T>
    class GenericRepository
    {
    public:
        GenericRepository();
        virtual ~GenericRepository();

        T create();
        T read(int id);
        bool update(T entity);
        bool remove(T entity);

    protected:
        bool runQuerry();

    private:
        QSqlQuery m_query;
    };
}

#endif // GENERIC_REPOSITORY_H
