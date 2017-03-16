#ifndef BASE_ENTITY_H
#define BASE_ENTITY_H

namespace data_source
{
    class BaseEntity
    {
    public:
        BaseEntity(int id);

        int id() const;

    private:
        const int m_id;
    };
}

#endif // BASE_ENTITY_H
