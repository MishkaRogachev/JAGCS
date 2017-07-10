#ifndef DATA_BASE_PRESENTER_H
#define DATA_BASE_PRESENTER_H

// Internal
#include "base_presenter.h"
#include "db_traits.h"

namespace domain
{
    class DomainEntry;
}

namespace presentation
{
    class DataBasePresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        explicit DataBasePresenter(domain::DomainEntry* entry, QObject* parent = nullptr);
        ~DataBasePresenter() override;

    public slots:
        void updateView();
        void updateConnected();
        void save();
        void tryConnect();

    protected:
        void connectView(QObject* view) override;

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // DATA_BASE_PRESENTER_H
