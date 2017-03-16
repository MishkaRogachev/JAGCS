#include "base_entity.h"

using namespace data_source;

BaseEntity::BaseEntity(int id, QObject* parent):
    QObject(parent),
    m_id(id)
{}

BaseEntity::~BaseEntity()
{}

int BaseEntity::id() const
{
    return m_id;
}
