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
        Q_PROPERTY(int fontPixelSize READ fontPixelSize WRITE setFontPixelSize)
        Q_PROPERTY(int spacing READ spacing WRITE setSpacing)
        Q_PROPERTY(int margins READ margins WRITE setMargins)
        Q_PROPERTY(int padding READ padding WRITE setPadding)

    public:
        int controlBaseSize() const;
        void setControlBaseSize(int controlBaseSize);

        int fontPixelSize() const;
        void setFontPixelSize(int fontPixelSize);

        int spacing() const;
        void setSpacing(int spacing);

        int margins() const;
        void setMargins(int margins);

        int padding() const;
        void setPadding(int padding);

    private:
        int m_controlBaseSize;
        int m_fontPixelSize;
        int m_spacing;
        int m_margins;
        int m_padding;
    };
}

#endif // SIZINGS_H
