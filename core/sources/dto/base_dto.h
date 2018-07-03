#ifndef BASE_DTO_H
#define BASE_DTO_H

// Qt
#include <QObject>

// Internal
#include "dto_traits.h"

namespace dto
{
    class BaseDto
    {
        Q_GADGET

        Q_PROPERTY(int id READ id WRITE setId)

    public:
        virtual ~BaseDto();

        int id() const;
        virtual void setId(int id);

    private:
        int m_id = 0;
    };
}

#endif // BASE_DTO_H
