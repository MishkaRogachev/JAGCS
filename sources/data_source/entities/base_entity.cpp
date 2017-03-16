#include "base_entity.h"

// Qt
#include <QtGlobal>

using namespace data_source;

BaseEntity::BaseEntity(int id):
    m_id(id),
    m_valid(false)
{}

BaseEntity::~BaseEntity()
{}

int BaseEntity::id() const
{
    return m_id;
}

bool BaseEntity::isValid() const
{
    return m_valid;
}

void BaseEntity::setValid(bool valid)
{
    m_valid = valid;
}
