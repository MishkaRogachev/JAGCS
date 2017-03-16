#ifndef BASE_ENTITY_H
#define BASE_ENTITY_H

// Qt
#include <QString>

class QSqlQuery;

namespace data_source
{
    class BaseEntity
    {
    public:
        BaseEntity(int id);
        virtual ~BaseEntity();

        int id() const;

        bool isValid() const;
        void setValid(bool isValid);

    private:
        const int m_id;
        bool m_valid;
    };
}

#endif // BASE_ENTITY_H
