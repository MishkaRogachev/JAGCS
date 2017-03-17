#include "base_entity.h"

// Qt
#include <QMetaProperty>
#include <QSqlQuery>
#include <QVariant>
#include <QDebug>

using namespace data_source;

BaseEntity::BaseEntity():
    m_id(0)
{}

BaseEntity::~BaseEntity()
{}

int BaseEntity::id() const
{
    return m_id;
}

void BaseEntity::setId(int id)
{
    m_id = id;
}

QList<QString> BaseEntity::fields() const
{
    const QMetaObject* meta = this->metaObject();
    QList<QString> list;

    for (int i = meta->propertyOffset(); i < meta->propertyCount(); ++i)
    {
        list.append(meta->property(i).name());
    }

    return list;
}

void BaseEntity::bindQuery(QSqlQuery& query, const QMetaObject& meta) const
{
    for (int i = meta.propertyOffset(); i < meta.propertyCount(); ++i)
    {
        query.bindValue(QString(":") + QString(meta.property(i).name()),
                        meta.property(i).read(this));
    }
}

void BaseEntity::updateFromQuery(const QSqlQuery& query, const QMetaObject& meta)
{
    for (int i = meta.propertyOffset(); i < meta.propertyCount(); ++i)
    {
        QVariant value = query.value(meta.property(i).name());

        // workaround for enums
        if (!meta.property(i).write(this, value) && !value.isNull())
        {
            meta.property(i).write(this, value.toInt());
        }
    }
}

QStringList BaseEntity::propertyNames(const QMetaObject& meta)
{
    QStringList list;

    for (int i = meta.propertyOffset(); i < meta.propertyCount(); ++i)
    {
        list.append(meta.property(i).name());
    }

    return list;
}

QString BaseEntity::insertString(const QMetaObject& meta)
{
    QStringList names =  BaseEntity::propertyNames(meta);
    QStringList values;

    for (const QString& name: names)
    {
        values.append(":" + name);
    }

    return "(" + names.join(", ") + ") VALUES (" + values.join(", ") + ")";
}

QString BaseEntity::updateString(const QMetaObject& meta)
{
    QStringList placeholders;

    for (const QString& name: BaseEntity::propertyNames(meta))
    {
        placeholders.append(name + " = :" + name);
    }

    return placeholders.join(", ") + " ";
}
