#ifndef BASE_ENTITY_H
#define BASE_ENTITY_H

// Qt
#include <QObject>

// Internal
#include "db_traits.h"

class QSqlQuery;

namespace data_source
{
    class BaseEntity: public QObject
    {
        Q_GADGET

        Q_PROPERTY(int id READ id WRITE setId)

    public:
        BaseEntity();
        virtual ~BaseEntity();

        int id() const;
        virtual void setId(int id);

    private:
        int m_id;
    };
}

#endif // BASE_ENTITY_H
