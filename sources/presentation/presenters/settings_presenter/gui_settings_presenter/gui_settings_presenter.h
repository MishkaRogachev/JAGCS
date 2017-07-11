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
        void save();

    protected:
        void connectView(QObject* view) override;
    };
}

#endif // GUI_SETTINGS_PRESENTER_H
