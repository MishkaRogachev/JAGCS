#ifndef STATUS_PRESENTER_H
#define STATUS_PRESENTER_H

#include <QObject>

namespace presentation
{
    class StatusPresenter: public QObject
    {
        Q_OBJECT

    public:
        explicit StatusPresenter(QObject* parent = nullptr);

    public slots:
        void quit();
    };
}

#endif // STATUS_PRESENTER_H
