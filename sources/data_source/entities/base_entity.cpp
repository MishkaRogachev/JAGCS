#include "base_entity.h"

// Qt
#include <QMetaProperty>
#include <QSqlQuery>
#include <QVariant>
#include <QDebug>

using namespace data_source;

BaseEntity::BaseEntity(int id, QObject* parent):
    QObject(parent),
    m_id(id)
{}

BaseEntity::~BaseEntity()
{}

int BaseEntity::id() const
{
    return m_id;
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

void BaseEntity::bindQuery(QSqlQuery& query) const
{
    const QMetaObject* meta = this->metaObject();

    for (int i = meta->propertyOffset(); i < meta->propertyCount(); ++i)
    {
        query.bindValue(QString(":") + QString(meta->property(i).name()),
                        meta->property(i).read(this));
    }
}

void BaseEntity::updateFromQuery(const QSqlQuery& query)
{
    const QMetaObject* meta = this->metaObject();

    for (int i = meta->propertyOffset(); i < meta->propertyCount(); ++i)
    {
        QVariant value = query.value(meta->property(i).name());

        // workaround for enums
        if (!meta->property(i).write(this, value) && !value.isNull())
        {
            meta->property(i).write(this, value.toInt());
        }
    }
}
