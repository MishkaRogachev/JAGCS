#ifndef COMMUNICATION_MANAGER_H
#define COMMUNICATION_MANAGER_H

// Qt
#include <QObject>

// Internal
#include "db_traits.h"

namespace db
{
    class DbEntry;
}

namespace comm
{
    class ICommunicatorFactory;
}

namespace domain
{
    class CommunicationManager: public QObject
    {
        Q_OBJECT

    public:
        CommunicationManager(comm::ICommunicatorFactory* commFactory,
                             db::DbEntry* entry,
                             QObject* parent = nullptr);
        ~CommunicationManager() override;

        db::LinkDescriptionPtrList links() const;

    public slots:
        void saveLink(const db::LinkDescriptionPtr& description);
        void removeLink(const db::LinkDescriptionPtr& description);

    signals:
        void linkAdded(const db::LinkDescriptionPtr& description);
        void linkRemoved(const db::LinkDescriptionPtr& description);
        void linkChanged(const db::LinkDescriptionPtr& description);
        void linkStatisticsChanged(const db::LinkDescriptionPtr& description,
                                   int sentBytes, int recvBytes);

    private slots:
        void onLinkStatisticsChanged();

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // COMMUNICATION_MANAGER_H
