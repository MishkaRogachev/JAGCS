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

int Sizings::inputControlHeight() const
{
    return m_inputControlHeight;
}

void Sizings::setInputControlHeight(int inputControlHeight)
{
    m_inputControlHeight = inputControlHeight;
}

int Sizings::fontSize() const
{
    return m_fontSize;
}

void Sizings::setFontSize(int fontSize)
{
    m_fontSize = fontSize;
}

int Sizings::secondaryFontSize() const
{
    return m_secondaryFontSize;
}

void Sizings::setSecondaryFontSize(int secondaryFontSize)
{
    m_secondaryFontSize = secondaryFontSize;
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

int Sizings::shadowSize() const
{
    return m_shadowSize;
}

void Sizings::setShadowSize(int shadowSize)
{
    m_shadowSize = shadowSize;
}
