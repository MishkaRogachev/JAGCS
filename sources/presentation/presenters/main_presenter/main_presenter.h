#ifndef MAIN_PRESENTER_H
#define MAIN_PRESENTER_H

#include "base_presenter.h"

namespace presentation
{
    class MainPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        enum Mode
        {
            NoMode,

            Control,
            Planning,
            Settings
        };

        explicit MainPresenter(QObject* parent = nullptr);
        ~MainPresenter() override;

        Mode mode() const;

    public slots:
        void setMode(int mode);

    protected:
        void connectView(QObject* view) override;

    private:
        class Impl;
        QScopedPointer<Impl> const d;

        Q_ENUM(Mode)
    };
}

#endif // MAIN_PRESENTER_H
