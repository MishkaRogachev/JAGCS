#ifndef PRESENTERS_FACTORY_H
#define PRESENTERS_FACTORY_H

#include <QObject>

namespace domain
{
    class DomainEntry;
}

namespace presentation
{
    class PresentersFactory: public QObject
    {
        Q_OBJECT

    public:
        explicit PresentersFactory(domain::DomainEntry* entry,
                                   QObject* parent = nullptr);

        Q_INVOKABLE QObject* createVideoPresenter(QObject* parent);
        Q_INVOKABLE QObject* createMapPresenter(QObject* parent);
        Q_INVOKABLE QObject* createStatusPresenter(QObject* parent);
        Q_INVOKABLE QObject* createFlightPresenter(QObject* parent);
        Q_INVOKABLE QObject* createSettingsPresenter(QObject* parent);

    private:
        domain::DomainEntry* m_entry;
        Q_DISABLE_COPY(PresentersFactory)
    };
}

#endif // PRESENTERS_FACTORY_H
