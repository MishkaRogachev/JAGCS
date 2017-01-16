#ifndef MAP_PRESENTER_H
#define MAP_PRESENTER_H

#include "base_presenter.h"

namespace presentation
{
    class MapPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        explicit MapPresenter(QObject* parent = nullptr);
        ~MapPresenter() override;

    public slots:
        void updateMapViewport();
        void saveMapViewport();

    protected:
        void connectView(QObject* view) override;
    };
}

#endif // MAP_PRESENTER_H
