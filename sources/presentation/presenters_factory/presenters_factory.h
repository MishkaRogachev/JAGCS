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

        Q_INVOKABLE QObject* createTopbarPresenter(QObject* view);

        Q_INVOKABLE QObject* createMapPresenter(QObject* view);
        Q_INVOKABLE QObject* createVideoPresenter(QObject* view);

        Q_INVOKABLE QObject* createCommunicationPresenter(QObject* view);
        Q_INVOKABLE QObject* createVehiclesPresenter(QObject* view);
        Q_INVOKABLE QObject* createPlanningPresenter(QObject* view);
        Q_INVOKABLE QObject* createAboutPresenter(QObject* view);

        Q_INVOKABLE QObject* createDatabasePresenter(QObject* view);
        Q_INVOKABLE QObject* createGuiSettingsPresenter(QObject* view);
        Q_INVOKABLE QObject* createJoystickSettingsPresenter(QObject* view);
        Q_INVOKABLE QObject* createMapSettingsPresenter(QObject* view);
        Q_INVOKABLE QObject* createNetworkSettingsPresenter(QObject* view);
        Q_INVOKABLE QObject* createVideoSettingsPresenter(QObject* view);
    };
}

#endif // PRESENTERS_FACTORY_H
