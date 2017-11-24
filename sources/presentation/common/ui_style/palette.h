#ifndef PALETTE_H
#define PALETTE_H

// Qt
#include <QObject>
#include <QColor>

namespace presentation
{
    class Palette
    {
        Q_GADGET

        Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor)
        Q_PROPERTY(QColor sunkenColor READ sunkenColor WRITE setSunkenColor)
        Q_PROPERTY(QColor raisedColor READ raisedColor WRITE setRaisedColor)
        Q_PROPERTY(QColor buttonColor READ buttonColor WRITE setButtonColor)
        Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor)
        Q_PROPERTY(QColor selectedTextColor READ selectedTextColor WRITE setSelectedTextColor)
        Q_PROPERTY(QColor highlightColor READ highlightColor WRITE setHighlightColor)
        Q_PROPERTY(QColor selectionColor READ selectionColor WRITE setSelectionColor)
        Q_PROPERTY(QColor linkColor READ linkColor WRITE setLinkColor)

        Q_PROPERTY(QColor dangerColor READ dangerColor WRITE setDangerColor)
        Q_PROPERTY(QColor cautionColor READ cautionColor WRITE setCautionColor)
        Q_PROPERTY(QColor positiveColor READ positiveColor WRITE setPositiveColor)

        Q_PROPERTY(QColor trackColor READ trackColor WRITE setTrackColor)
        Q_PROPERTY(QColor missionColor READ missionColor WRITE setMissionColor)
        Q_PROPERTY(QColor activeMissionColor READ activeMissionColor WRITE setActiveMissionColor)

        Q_PROPERTY(QColor skyColor READ skyColor WRITE setSkyColor)
        Q_PROPERTY(QColor groundColor READ groundColor WRITE setGroundColor)

    public:
        QColor backgroundColor() const;
        void setBackgroundColor(QColor backgroundColor);

        QColor sunkenColor() const;
        void setSunkenColor(QColor sunkenColor);

        QColor raisedColor() const;
        void setRaisedColor(QColor raisedColor);

        QColor buttonColor() const;
        void setButtonColor(QColor buttonColor);

        QColor textColor() const;
        void setTextColor(QColor textColor);

        QColor selectedTextColor() const;
        void setSelectedTextColor(QColor selectedTextColor);

        QColor highlightColor() const;
        void setHighlightColor(QColor highlightColor);

        QColor selectionColor() const;
        void setSelectionColor(QColor selectionColor);

        QColor linkColor() const;
        void setLinkColor(QColor linkColor);

        QColor dangerColor() const;
        void setDangerColor(QColor dangerColor);

        QColor cautionColor() const;
        void setCautionColor(QColor cautionColor);

        QColor positiveColor() const;
        void setPositiveColor(QColor positiveColor);

        QColor trackColor() const;
        void setTrackColor(QColor trackColor);

        QColor missionColor() const;
        void setMissionColor(QColor missionColor);

        QColor activeMissionColor() const;
        void setActiveMissionColor(QColor activeMissionColor);

        QColor skyColor() const;
        void setSkyColor(QColor skyColor);

        QColor groundColor() const;
        void setGroundColor(QColor groundColor);

    private:
        QColor m_backgroundColor;
        QColor m_sunkenColor;
        QColor m_raisedColor;
        QColor m_buttonColor;
        QColor m_textColor;
        QColor m_selectedTextColor;
        QColor m_highlightColor;
        QColor m_selectionColor;
        QColor m_linkColor;
        QColor m_dangerColor;
        QColor m_cautionColor;
        QColor m_positiveColor;
        QColor m_trackColor;
        QColor m_missionColor;
        QColor m_activeMissionColor;
        QColor m_skyColor;
        QColor m_groundColor;
    };
}

#endif // PALETTE_H
