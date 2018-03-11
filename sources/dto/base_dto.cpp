#include "base_dto.h"

using namespace dto;

BaseDto::~BaseDto()
{}

int BaseDto::id() const
{
    return m_id;
}

void BaseDto::setId(int id)
{
    m_id = id;
}

