#include "base_dao.h"

using namespace dao;

BaseDao::~BaseDao()
{}

int BaseDao::id() const
{
    return m_id;
}

void BaseDao::setId(int id)
{
    m_id = id;
}

