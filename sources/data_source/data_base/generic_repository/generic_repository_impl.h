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
bool GenericRepository<T>::insert(const QSharedPointer<T>& entity)
{
    m_query.prepare("INSERT INTO " + T::tableName() + " " +
                    entity->insertString(T::staticMetaObject));
    entity->bindQuery(m_query, T::staticMetaObject);

    if (this->runQuerry())
    {
        entity->setId(m_query.lastInsertId().toInt());
        m_map[entity->id()] = entity;
        return true;
    }
    return false;
}

template<class T>
QSharedPointer<T> GenericRepository<T>::read(int id, bool reload)
{
    bool contains = m_map.contains(id);

    if (!contains || reload)
    {
        m_query.prepare("SELECT * FROM " + T::tableName() + " WHERE id = :id");
        m_query.bindValue(":id", id);

        if (this->runQuerry() && m_query.next())
        {
            QSharedPointer<T> item = contains ? m_map[id] :
                                                QSharedPointer<T>::create();
            item->setId(id);
            item->updateFromQuery(m_query, T::staticMetaObject);
            m_map[id] = item;
            return item;
        }
        return QSharedPointer<T>();
    }
    return m_map[id];
}

template<class T>
bool GenericRepository<T>::update(const QSharedPointer<T>& entity)
{
    m_query.prepare("UPDATE " + T::tableName() + " SET " +
                    entity->updateString(T::staticMetaObject) +
                    "WHERE id = :id");

    m_query.bindValue(":id", entity->id());
    entity->bindQuery(m_query, T::staticMetaObject);

    if (!this->runQuerry()) return false;
    m_map[entity->id()] = entity;
    return true;
}

template<class T>
bool GenericRepository<T>::remove(const QSharedPointer<T>& entity)
{
    m_query.prepare("DELETE FROM " + T::tableName() + " WHERE id = :id");
    m_query.bindValue(":id", entity->id());
    if (!this->runQuerry()) return false;
    this->unload(entity->id());
    entity->setId(0);
    return true;
}

template<class T>
bool GenericRepository<T>::save(const QSharedPointer<T>& entity)
{
    if (entity->id() > 0)
    {
        if (!this->update(entity)) return false;
    }
    else
    {
        if (!this->insert(entity)) return false;
    }
    return true;
}

template<class T>
bool GenericRepository<T>::contains(int id)
{
    return m_map.contains(id);
}

template<class T>
void GenericRepository<T>::unload(int id)
{
    m_map.remove(id);
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
