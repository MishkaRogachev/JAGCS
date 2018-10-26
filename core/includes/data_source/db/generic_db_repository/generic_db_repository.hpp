#ifndef GENERIC_DB_REPOSITORY_IMPL_H
#define GENERIC_DB_REPOSITORY_IMPL_H

#include "generic_db_repository.h"

// Qt
#include <QMetaProperty>
#include <QSqlError>
#include <QDebug>

namespace
{
    const QString comma = ", ";
}

using namespace data_source;

template<class T>
GenericDbRepository<T>::GenericDbRepository(const QString& tableName):
    m_tableName(tableName)
{
    m_query.exec("PRAGMA table_info(" + m_tableName + ")");
    while (m_query.next()) m_columnNames.append(m_query.value(1).toString());
}

template<class T>
GenericDbRepository<T>::~GenericDbRepository()
{}

template<class T>
bool GenericDbRepository<T>::insert(const QSharedPointer<T>& entity)
{
    QStringList names;
    QStringList values;

    for (const QString& name: this->propertyNames(T::staticMetaObject))
    {
        if (!m_columnNames.contains(name)) continue;

        names.append(name);
        values.append(":" + name);
    }

    QString namesJoin = names.join(::comma);
    QString valuesJoin = values.join(::comma);
    m_query.prepare("INSERT INTO " + m_tableName + " (" +
                    namesJoin + ") VALUES (" + valuesJoin + ")");
    this->bindQuery(m_query, T::staticMetaObject, entity.data());

    return this->runQuerry();
}

template<class T>
QSharedPointer<T> GenericDbRepository<T>::read(int id, bool reload)
{
    bool contains = m_map.contains(id);

    if (!contains || reload)
    {
        m_query.prepare("SELECT * FROM " + m_tableName + " WHERE id = :id");
        m_query.bindValue(":id", id);

        if (this->runQuerry() && m_query.next())
        {
            QSharedPointer<T> entity = contains ? m_map[id] : QSharedPointer<T>::create();
            this->updateFromQuery(m_query, T::staticMetaObject, entity.data());
            m_map[id] = entity;
            return entity;
        }
        return QSharedPointer<T>();
    }
    return m_map[id];
}

template<class T>
bool GenericDbRepository<T>::update(const QSharedPointer<T>& entity)
{
    QStringList placeholders;

    for (const QString& name: this->propertyNames(T::staticMetaObject))
    {
        if (m_columnNames.contains(name)) placeholders.append(name + " = :" + name);
    }

    QString placeholdersJoin = placeholders.join(::comma);
    m_query.prepare("UPDATE " + m_tableName + " SET " + placeholdersJoin + " WHERE id = :id");

    m_query.bindValue(":id", m_map.key(entity));
    this->bindQuery(m_query, T::staticMetaObject, entity.data());

    return this->runQuerry();
}

template<class T>
bool GenericDbRepository<T>::remove(const QSharedPointer<T>& entity)
{
    m_query.prepare("DELETE FROM " + m_tableName + " WHERE id = :id");
    m_query.bindValue(":id", m_map.key(entity));

    return this->runQuerry();
}

template<class T>
bool GenericDbRepository<T>::save(const QSharedPointer<T>& entity)
{
    if (m_map.key(entity, 0))
    {
        return this->update(entity);
    }
    else
    {
        return this->insert(entity);
    }
}

template<class T>
bool GenericDbRepository<T>::contains(int id)
{
    return m_map.contains(id);
}

template<class T>
void GenericDbRepository<T>::unload(int id)
{
    m_map.remove(id);
}

template<class T>
void GenericDbRepository<T>::clear()
{
    m_map.clear();
}

template<class T>
QList<int> GenericDbRepository<T>::selectId(const QString& condition)
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
QList<int> GenericDbRepository<T>::loadedIds() const
{
    return m_map.keys();
}

template<class T>
QList<QSharedPointer<T> > GenericDbRepository<T>::loadedEntities() const
{
    return m_map.values();
}

template<class T>
bool GenericDbRepository<T>::runQuerry()
{
    if (m_query.exec()) return true;

    // TODO: log with db log level
    qDebug() << m_query.lastError() << m_query.executedQuery();
    return false;
}

template<class T>
QStringList GenericDbRepository<T>::propertyNames(const QMetaObject& meta)
{
    QStringList list;

    for (int i = meta.propertyOffset(); i < meta.propertyCount(); ++i)
    {
        list.append(meta.property(i).name());
    }

    return list;
}

template<class T>
void GenericDbRepository<T>::bindQuery(QSqlQuery& query, const QMetaObject& meta, T* entity)
{
    for (int i = meta.propertyOffset(); i < meta.propertyCount(); ++i)
    {
        QString name = meta.property(i).name();
        if (!m_columnNames.contains(name)) continue;

        query.bindValue(QString(":") + name, meta.property(i).readOnGadget(entity));
    }
}

template<class T>
void GenericDbRepository<T>::updateFromQuery(const QSqlQuery& query, const QMetaObject& meta, T* entity)
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

#endif // GENERIC_DB_REPOSITORY_IMPL_H
