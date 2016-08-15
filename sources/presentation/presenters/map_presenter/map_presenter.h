#ifndef MAP_PRESENTER_H
#define MAP_PRESENTER_H

#include <QObject>

namespace presentation
{
    class MapPresenter : public QObject
    {
        Q_OBJECT

    public:
        explicit MapPresenter(QObject* parent = nullptr);

    };
}

#endif // MAP_PRESENTER_H
