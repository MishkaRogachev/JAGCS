#ifndef DATA_BASE_PRESENTER_H
#define DATA_BASE_PRESENTER_H

// Internal
#include "base_presenter.h"
#include "dao_traits.h"

namespace presentation
{
    class DataBasePresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        explicit DataBasePresenter(QObject* parent = nullptr);
        ~DataBasePresenter() override;

    public slots:
        void updateView();
        void updateConnected();
        void updateLog();
        void clearLog();
        void save();
        void migrate();
        void tryConnect();

    protected:
        void connectView(QObject* view) override;

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // DATA_BASE_PRESENTER_H
