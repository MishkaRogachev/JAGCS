#ifndef BASE_ENTITY_H
#define BASE_ENTITY_H

// Qt
#include <QObject>

// Internal
#include "identity_traits.h"

class QSqlQuery;

namespace data_source
{
    class BaseEntity: public QObject
    {
        Q_GADGET

        Q_PROPERTY(int id READ id WRITE setId)

    public:
        explicit BaseEntity(IdentityMap* iMap);
        virtual ~BaseEntity();

        int id() const;
        void setId(int id);

        virtual QList<QString> fields() const;

        virtual void bindQuery(QSqlQuery& query, const QMetaObject& meta) const;
        virtual void updateFromQuery(const QSqlQuery& query, const QMetaObject& meta);

        static QStringList propertyNames(const QMetaObject& meta);
        static QString insertString(const QMetaObject& meta);
        static QString updateString(const QMetaObject& meta);

    protected:
        IdentityMap* const m_iMap;

    private:
        int m_id;
    };
}

#endif // BASE_ENTITY_H
