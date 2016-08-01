#ifndef PRESENTERS_FACTORY_H
#define PRESENTERS_FACTORY_H

#include <QObject>

namespace presentation
{
    class PresentersFactory: public QObject
    {
        Q_OBJECT

    public:
        explicit PresentersFactory(QObject* parent = nullptr);

        Q_INVOKABLE QObject* createVideoPresenter(QObject* parent);

    private:
        Q_DISABLE_COPY(PresentersFactory)
    };
}

#endif // PRESENTERS_FACTORY_H
