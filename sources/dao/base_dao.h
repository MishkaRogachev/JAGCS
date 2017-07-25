#ifndef BASE_DAO_H
#define BASE_DAO_H

// Qt
#include <QObject>

// Internal
#include "dao_traits.h"

namespace dao
{
    class BaseDao
    {
        Q_GADGET

        Q_PROPERTY(int id READ id WRITE setId)

    public:
        virtual ~BaseDao();

        int id() const;
        virtual void setId(int id);

    private:
        int m_id = 0;
    };
}

#endif // BASE_DAO_H
