#ifndef GENERIC_REPOSITORY_IMPL_H
#define GENERIC_REPOSITORY_IMPL_H

#include "generic_repository.h"

// Qt
#include <QSqlError>
#include <QDebug>

using namespace data_source;

template<class T>
GenericRepository<T>::GenericRepository()
{}

template<class T>
GenericRepository<T>::~GenericRepository()
{}

template<class T>
bool GenericRepository<T>::insert(T* entity)
{
    m_query.prepare("INSERT INTO " + T::tableName() + " " +
                    entity->insertString(T::staticMetaObject));
    entity->bindQuery(m_query, T::staticMetaObject);

    if (this->runQuerry())
    {
        entity->setId(m_query.lastInsertId().toInt());
        return true;
    }
    return false;
}

template<class T>
T* GenericRepository<T>::read(int id, IdentityMap* iMap)
{
    m_query.prepare("SELECT * FROM " + T::tableName() + " WHERE id = :id");
    m_query.bindValue(":id", id);

    if (this->runQuerry() && m_query.next())
    {
        T* entity = new T(iMap);
        entity->setId(id);
        entity->updateFromQuery(m_query, T::staticMetaObject);
        return entity;
    }
    return nullptr;
}

template<class T>
bool GenericRepository<T>::update(T* entity)
{
    m_query.prepare("UPDATE " + T::tableName() + " SET " +
                    entity->updateString(T::staticMetaObject) +
                    "WHERE id = :id");

    m_query.bindValue(":id", entity->id());
    entity->bindQuery(m_query, T::staticMetaObject);
    return this->runQuerry();
}

template<class T>
bool GenericRepository<T>::remove(T* entity)
{
    m_query.prepare("DELETE FROM " + T::tableName() + " WHERE id = :id");
    m_query.bindValue(":id", entity->id());
    return this->runQuerry();
}

template<class T>
QList<T*> GenericRepository<T>::select(const QString& condition)
{
    QList<T*> entities;

    m_query.prepare("SELECT * FROM " + T::tableName() + " WHERE " + condition);

    if (!this->runQuerry()) return entities;

    while (m_query.next())
    {
        T* entity = new T();
        entity->setId(m_query.value("id").toInt());
        entity->updateFromQuery(m_query, T::staticMetaObject);
        entities.append(entity);
    }

    return entities;
}

template<class T>
QList<int> GenericRepository<T>::selectId(const QString& condition)
{
    QList<int> idList;

    m_query.prepare("SELECT id FROM " + T::tableName() + " WHERE " + condition);

    if (!this->runQuerry()) return idList;

    while (m_query.next()) idList.append(m_query.value("id").toInt());

    return idList;
}

template<class T>
bool GenericRepository<T>::runQuerry()
{
    if (m_query.exec()) return true;
    qWarning() << m_query.lastError() << m_query.executedQuery();
    return false;
}

#endif // GENERIC_REPOSITORY_IMPL_H
