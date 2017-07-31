#ifndef MAIN_PRESENTER_H
#define MAIN_PRESENTER_H

#include "base_presenter.h"

namespace presentation
{
    class MainPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        explicit MainPresenter(QObject* parent = nullptr);
        ~MainPresenter() override;

    public slots:
        void setMode(const QString& mode);

    protected:
        void connectView(QObject* view) override;

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // MAIN_PRESENTER_H
