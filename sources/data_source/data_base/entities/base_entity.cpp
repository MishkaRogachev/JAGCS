#include "base_entity.h"

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

