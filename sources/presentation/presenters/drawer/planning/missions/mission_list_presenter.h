#ifndef MISSION_LIST_PRESENTER_H
#define MISSION_LIST_PRESENTER_H

// Internal
#include "base_presenter.h"

// Qt
#include <QGeoCoordinate>

namespace domain
{
    class MissionService;
}

namespace presentation
{
    class MissionListPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        explicit MissionListPresenter(QObject* parent = nullptr);
        ~MissionListPresenter() override;

    public slots:
        void addMission(const QGeoCoordinate& coordinate);
        void filter(const QString& filterString);

    protected:
        void connectView(QObject* view);

    private:
         class Impl;
         QScopedPointer<Impl> const d;
    };
}

#endif // MISSION_LIST_PRESENTER_H
