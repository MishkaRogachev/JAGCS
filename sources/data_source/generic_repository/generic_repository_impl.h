#include "generic_repository.h"

// Qt
#include <QSqlError>
#include <QDebug>

using namespace data_source;

template<class T>
GenericRepository<T>::GenericRepository()
{}

template<class T>
T GenericRepository<T>::create()
{
    m_query.prepare("INSERT INTO " + T::tableName() + " " + T::insertString());

    if (this->runQuerry()) return T(m_query.lastInsertId().toInt());
    return T(-1);
}

template<class T>
T GenericRepository<T>::read(int id)
{
    m_query.prepare("SELECT * FROM " + T::tableName() + " WHERE id = :id");
    m_query.bindValue(":id", id);

    T entity(id);

    if (this->runQuerry() && m_query.next())
    {
        entity.updateFromQuery(m_query);
    }
    return entity;
}

template<class T>
bool GenericRepository<T>::update(T entity)
{
    m_query.prepare("UPDATE " + T::tableName() + " SET " +
                     T::updateString() +
                     "WHERE id = :id");

    m_query.bindValue(":id", entity.id());
    entity.bindQuery(m_query);
    return this->runQuerry();
}

template<class T>
bool GenericRepository<T>::remove(T entity)
{
    m_query.prepare("DELETE FROM " + T::tableName() +" WHERE id = :id");
    m_query.bindValue(":id", entity.id());
    return this->runQuerry();
}

template<class T>
bool GenericRepository<T>::runQuerry()
{
    if (m_query.exec()) return true;
    qWarning() << m_query.lastError() << m_query.executedQuery();
    return false;
}
