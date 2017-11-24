#include "sizings.h"

using namespace presentation;

int Sizings::controlBaseSize() const
{
    return m_controlBaseSize;
}

void Sizings::setControlBaseSize(int controlBaseSize)
{
    m_controlBaseSize = controlBaseSize;
}

int Sizings::fontPixelSize() const
{
    return m_fontPixelSize;
}

void Sizings::setFontPixelSize(int fontPixelSize)
{
    m_fontPixelSize = fontPixelSize;
}

int Sizings::spacing() const
{
    return m_spacing;
}

void Sizings::setSpacing(int spacing)
{
    m_spacing = spacing;
}

int Sizings::margins() const
{
    return m_margins;
}

void Sizings::setMargins(int margins)
{
    m_margins = margins;
}

int Sizings::padding() const
{
    return m_padding;
}

void Sizings::setPadding(int padding)
{
    m_padding = padding;
}
