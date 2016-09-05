#ifndef CONNECTION_PRESENTER_H
#define CONNECTION_PRESENTER_H

#include "base_presenter.h"

namespace domain
{
    class ConnectionManager;
    class SettingsProvider;
}

namespace presentation
{
    class ConnectionPresenter: public BasePresenter
    {
        Q_OBJECT

        Q_PROPERTY(QList<QObject*> links READ links NOTIFY linksChanged)

    public:
        explicit ConnectionPresenter(domain::ConnectionManager* manager,
                                     domain::SettingsProvider* settings,
                                     QObject* view);
        ~ConnectionPresenter() override;

        QList<QObject*> links() const;

    public slots:
        void addSerialLink();
        void addUdpLink();

    signals:
        void linksChanged(QList<QObject*> links);

    private:
        class Impl;
        Impl* const d;
    };
}

#endif // CONNECTION_PRESENTER_H
