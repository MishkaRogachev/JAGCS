#ifndef MAIN_PRESENTER_H
#define MAIN_PRESENTER_H

#include "base_presenter.h"

namespace domain
{
    class DomainEntry;
}

namespace presentation
{
    class MainPresenter: public BasePresenter
    {
    public:
        explicit MainPresenter(domain::DomainEntry* entry,
                               QObject* object = nullptr);
        ~MainPresenter() override;

    public slots:
        void setMode(const QString& mode);

    protected:
        void connectView(QObject* view) override;

    private:
        class Impl;
        Impl* const d;
    };
}

#endif // MAIN_PRESENTER_H
