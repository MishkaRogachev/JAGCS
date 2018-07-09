#ifndef DATABASE_PRESENTER_H
#define DATABASE_PRESENTER_H

// Internal
#include "base_presenter.h"
#include "db_manager.h"

namespace presentation
{
    class DatabasePresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        explicit DatabasePresenter(QObject* parent = nullptr);

    public slots:
        void updatePath();
        void updateConnected();
        void updateLog();
        void clearLog();
        void savePath();
        void migrate();
        void tryConnect();

    private:
        data_source::DbManager m_manager;
    };
}

#endif // DATABASE_PRESENTER_H
