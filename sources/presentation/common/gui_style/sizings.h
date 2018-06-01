#ifndef SIZINGS_H
#define SIZINGS_H

// Qt
#include <QObject>

namespace presentation
{
    class Sizings
    {
        Q_GADGET

        Q_PROPERTY(int controlBaseSize READ controlBaseSize WRITE setControlBaseSize)
        Q_PROPERTY(int primaryFontSize READ primaryFontSize WRITE setFontPixelSize)
        Q_PROPERTY(int secondaryFontSize READ secondaryFontSize WRITE setSecondaryFontSize)
        Q_PROPERTY(int spacing READ spacing WRITE setSpacing)
        Q_PROPERTY(int margins READ margins WRITE setMargins)
        Q_PROPERTY(int padding READ padding WRITE setPadding)
        Q_PROPERTY(int shadowSize READ shadowSize WRITE setShadowSize)

    public:
        int controlBaseSize() const;
        void setControlBaseSize(int controlBaseSize);

        int primaryFontSize() const;
        void setFontPixelSize(int primaryFontSize);

        int secondaryFontSize() const;
        void setSecondaryFontSize(int secondaryFontSize);

        int spacing() const;
        void setSpacing(int spacing);

        int margins() const;
        void setMargins(int margins);

        int padding() const;
        void setPadding(int padding);

        int shadowSize() const;
        void setShadowSize(int shadowSize);

    private:
        int m_controlBaseSize;
        int m_primaryFontSize;
        int m_secondaryFontSize;
        int m_spacing;
        int m_margins;
        int m_padding;
        int m_shadowSize;
    };
}

#endif // SIZINGS_H
