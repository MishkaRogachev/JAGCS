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

    protected:
        void connectView(QObject* view) override;
    };
}

#endif // MAP_PRESENTER_H
