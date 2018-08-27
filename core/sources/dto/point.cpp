#include "point.h"

using namespace dto;

double Point::x() const
{
    return m_x;
}

void Point::setX(double x)
{
    m_x = x;
}

double Point::y() const
{
    return m_y;
}

void Point::setY(double y)
{
    m_y = y;
}

double Point::z() const
{
    return m_Z;
}

void Point::setZ(double Z)
{
    m_Z = Z;
}

Point::Frame Point::frame() const
{
    return m_frame;
}

void Point::setFrame(Frame frame)
{
    m_frame = frame;
}
