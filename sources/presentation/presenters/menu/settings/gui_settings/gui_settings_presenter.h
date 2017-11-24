#ifndef GUI_SETTINGS_PRESENTER_H
#define GUI_SETTINGS_PRESENTER_H

#include "base_presenter.h"

namespace presentation
{
    class GuiSettingsPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        explicit GuiSettingsPresenter(QObject* parent = nullptr);
        ~GuiSettingsPresenter() override;

    public slots:
        void updateView();
        void save();

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // GUI_SETTINGS_PRESENTER_H
