#ifndef SETTINGS_PRESENTER_H
#define SETTINGS_PRESENTER_H

#include "base_presenter.h"

namespace presentation
{
    class SettingsPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        explicit SettingsPresenter(QObject* parent = nullptr);
        ~SettingsPresenter() override;

    public slots:
        void show();
        void hide();

    protected:
        void connectView(QObject* view) override;

    private slots:
        void onRequestPresenter(const QString& view);

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // SETTING_SPRESENTER_H
