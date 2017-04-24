#include "base_entity.h"

using namespace db;

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

