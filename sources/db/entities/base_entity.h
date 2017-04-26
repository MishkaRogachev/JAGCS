#ifndef BASE_ENTITY_H
#define BASE_ENTITY_H

// Qt
#include <QObject>

// Internal
#include "db_traits.h"

namespace db
{
    class BaseEntity
    {
        Q_GADGET

        Q_PROPERTY(int id READ id WRITE setId)

    public:
        virtual ~BaseEntity();

        int id() const;
        virtual void setId(int id);

    private:
        int m_id = 0;
    };
}

#endif // BASE_ENTITY_H
