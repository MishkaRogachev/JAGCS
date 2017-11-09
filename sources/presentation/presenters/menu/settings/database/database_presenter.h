#ifndef DATABASE_PRESENTER_H
#define DATABASE_PRESENTER_H

// Internal
#include "base_presenter.h"
#include "dao_traits.h"

namespace presentation
{
    class DatabasePresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        explicit DatabasePresenter(QObject* parent = nullptr);
        ~DatabasePresenter() override;

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

#endif // DATABASE_PRESENTER_H
