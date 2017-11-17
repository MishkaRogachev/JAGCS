#ifndef GENERIC_REPOSITORY_IMPL_H
#define GENERIC_REPOSITORY_IMPL_H

#include "generic_repository.h"

// Qt
#include <QMetaProperty>
#include <QSqlError>
#include <QDebug>

using namespace db;

template<class T>
GenericRepository<T>::GenericRepository(const QString& tableName):
    m_tableName(tableName)
{
    m_query.exec("PRAGMA table_info(" + m_tableName + ")");
    while (m_query.next()) m_columnNames.append(m_query.value(1).toString());
}

template<class T>
GenericRepository<T>::~GenericRepository()
{}

template<class T>
bool GenericRepository<T>::insert(const QSharedPointer<T>& entity)
{
    QStringList names;
    QStringList values;

    for (const QString& name: this->propertyNames(T::staticMetaObject))
    {
        if (!m_columnNames.contains(name)) continue;

        names.append(name);
        values.append(":" + name);
    }

    m_query.prepare("INSERT INTO " + m_tableName + " (" +
                    names.join(", ") + ") VALUES (" + values.join(", ") + ")");
    this->bindQuery(m_query, T::staticMetaObject, entity.data());

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
        m_query.prepare("SELECT * FROM " + m_tableName + " WHERE id = :id");
        m_query.bindValue(":id", id);

        if (this->runQuerry() && m_query.next())
        {
            QSharedPointer<T> entity = contains ? m_map[id] :
                                                  QSharedPointer<T>::create();
            entity->setId(id);
            this->updateFromQuery(m_query, T::staticMetaObject, entity.data());
            m_map[id] = entity;
            return entity;
        }
        return QSharedPointer<T>();
    }
    return m_map[id];
}

template<class T>
bool GenericRepository<T>::update(const QSharedPointer<T>& entity)
{
    QStringList placeholders;

    for (const QString& name: this->propertyNames(T::staticMetaObject))
    {
        if (m_columnNames.contains(name)) placeholders.append(name + " = :" + name);
    }

    m_query.prepare("UPDATE " + m_tableName + " SET " +
                    placeholders.join(", ") + " WHERE id = :id");

    m_query.bindValue(":id", entity->id());
    this->bindQuery(m_query, T::staticMetaObject, entity.data());

    if (!this->runQuerry()) return false;
    m_map[entity->id()] = entity;
    return true;
}

template<class T>
bool GenericRepository<T>::remove(const QSharedPointer<T>& entity)
{
    m_query.prepare("DELETE FROM " + m_tableName + " WHERE id = :id");
    m_query.bindValue(":id", entity->id());
    if (!this->runQuerry()) return false;
    this->unload(entity->id());
//    entity->setId(0);
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
void GenericRepository<T>::clear()
{
    m_map.clear();
}

template<class T>
QList<int> GenericRepository<T>::selectId(const QString& condition)
{
    QList<int> idList;

    QString string("SELECT id FROM " + m_tableName);
    if (!condition.isEmpty()) string += (" " + condition);
    m_query.prepare(string);

    if (!this->runQuerry()) return idList;

    while (m_query.next()) idList.append(m_query.value("id").toInt());

    return idList;
}

template<class T>
QList<int> GenericRepository<T>::loadedIds() const
{
    return m_map.keys();
}

template<class T>
QList<QSharedPointer<T> > GenericRepository<T>::loadedEntities() const
{
    return m_map.values();
}

template<class T>
bool GenericRepository<T>::runQuerry()
{
    if (m_query.exec()) return true;
    qWarning() << m_query.lastError() << m_query.executedQuery();
    return false;
}

template<class T>
QStringList GenericRepository<T>::propertyNames(const QMetaObject& meta)
{
    QStringList list;

    for (int i = meta.propertyOffset(); i < meta.propertyCount(); ++i)
    {
        list.append(meta.property(i).name());
    }

    return list;
}

template<class T>
void GenericRepository<T>::bindQuery(QSqlQuery& query, const QMetaObject& meta, T* entity)
{
    for (int i = meta.propertyOffset(); i < meta.propertyCount(); ++i)
    {
        QString name = meta.property(i).name();
        if (!m_columnNames.contains(name)) continue;

        query.bindValue(QString(":") + name, meta.property(i).readOnGadget(entity));
    }
}

template<class T>
void GenericRepository<T>::updateFromQuery(const QSqlQuery& query, const QMetaObject& meta, T* entity)
{
    for (int i = meta.propertyOffset(); i < meta.propertyCount(); ++i)
    {
        QString name = meta.property(i).name();
        if (!m_columnNames.contains(name)) continue;

        QVariant value = query.value(meta.property(i).name());

        // workaround for enums
        if (!meta.property(i).writeOnGadget(entity, value) && !value.isNull())
        {
            meta.property(i).writeOnGadget(entity, value.toInt());
        }
    }
}

#endif // GENERIC_REPOSITORY_IMPL_H
