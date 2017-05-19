#ifndef COMMUNICATION_SERVICE_H
#define COMMUNICATION_SERVICE_H

// Qt
#include <QObject>

// Internal
#include "db_traits.h"

namespace db
{
    class DbFacade;
}

namespace comm
{
    class ICommunicatorFactory;
}

namespace domain
{
    class CommunicationService: public QObject
    {
        Q_OBJECT

    public:
        CommunicationService(comm::ICommunicatorFactory* commFactory,
                             db::DbFacade* facade,
                             QObject* parent = nullptr);
        ~CommunicationService() override;

    public slots:
        void setLinkConnected(const db::LinkDescriptionPtr& description, bool connected);

    private slots:
        void onLinkAdded(const db::LinkDescriptionPtr& description);
        void onLinkChanged(const db::LinkDescriptionPtr& description);
        void onLinkRemoved(const db::LinkDescriptionPtr& description);
        void onLinkStatisticsChanged();

    signals:
        void linkStatisticsChanged(const db::LinkDescriptionPtr& description);

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // COMMUNICATION_SERVICE_H
