#ifndef PRESENTERS_FACTORY_H
#define PRESENTERS_FACTORY_H

#include <QObject>

namespace domain
{
    class SettingsProvider;
}

namespace presentation
{
    class PresentersFactory: public QObject
    {
        Q_OBJECT

    public:
        explicit PresentersFactory(domain::SettingsProvider* settings,
                                   QObject* parent = nullptr);

        Q_INVOKABLE QObject* createStatusPresenter(QObject* parent);
        Q_INVOKABLE QObject* createVideoPresenter(QObject* parent);
        Q_INVOKABLE QObject* createMapPresenter(QObject* parent);

        Q_INVOKABLE QObject* createVideoSettingsPresenter(QObject* parent);
        Q_INVOKABLE QObject* createNetworkSettingsPresenter(QObject* parent);

    private:
        domain::SettingsProvider* m_settings;
        Q_DISABLE_COPY(PresentersFactory)
    };
}

#endif // PRESENTERS_FACTORY_H
