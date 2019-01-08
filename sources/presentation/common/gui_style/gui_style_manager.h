#ifndef GUI_STYLE_MANAGER_H
#define GUI_STYLE_MANAGER_H

// Qt
#include <QObject>

class ThemeConfigurator;

namespace presentation
{
    class GuiStyleManager: public QObject
    {
        Q_OBJECT

    public:
        enum PaletteStyle
        {
            Night,
            Day
        };

        explicit GuiStyleManager(QObject* parent = nullptr);
        ~GuiStyleManager();

    public slots:
        void setPaletteStyle(PaletteStyle paletteStyle);
        void loadSettingsPalette();

        void setSizings(int baseSize);
        void loadSettingsSizings();

    private:
        Q_ENUM(PaletteStyle)

        ThemeConfigurator* m_configurator;
    };
}

#endif // GUI_STYLE_MANAGER_H
