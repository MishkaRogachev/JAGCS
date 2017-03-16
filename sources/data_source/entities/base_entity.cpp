#include "base_entity.h"

using namespace data_source;

BaseEntity::BaseEntity(int id):
    m_id(id)
{}

int BaseEntity::id() const
{
    return m_id;
}
