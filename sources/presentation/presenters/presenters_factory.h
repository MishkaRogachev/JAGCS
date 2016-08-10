#ifndef PRESENTERS_FACTORY_H
#define PRESENTERS_FACTORY_H

#include <QObject>

class SettingsProvider;

namespace presentation
{
    class PresentersFactory: public QObject
    {
        Q_OBJECT

    public:
        explicit PresentersFactory(SettingsProvider* settings,
                                   QObject* parent = nullptr);

        Q_INVOKABLE QObject* createStatusPresenter(QObject* parent);
        Q_INVOKABLE QObject* createVideoPresenter(QObject* parent);
        Q_INVOKABLE QObject* createNetworkSettingsPresenter(QObject* parent);

    private:
        SettingsProvider* m_settings;
        Q_DISABLE_COPY(PresentersFactory)
    };
}

#endif // PRESENTERS_FACTORY_H
