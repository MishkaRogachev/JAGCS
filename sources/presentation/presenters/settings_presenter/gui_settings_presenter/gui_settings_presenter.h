#ifndef GUI_SETTINGS_PRESENTER_H
#define GUI_SETTINGS_PRESENTER_H

#include "base_presenter.h"

namespace presentation
{
    class GuiSettingsPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        explicit GuiSettingsPresenter(QObject* parent);

    public slots:
        void updateView();

    protected:
        void connectView(QObject* view) override;

    private slots:
        void onSetUiSize(int size);
        void onSetPaletteStyle(int paletteStyle);
    };
}

#endif // GUI_SETTINGS_PRESENTER_H
