#ifndef COMMUNICATION_MANAGER_H
#define COMMUNICATION_MANAGER_H

// Qt
#include <QObject>

// Internal
#include "db_traits.h"

namespace data_source
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
                             data_source::DbEntry* entry,
                             QObject* parent = nullptr);
        ~CommunicationManager() override;

        data_source::LinkDescriptionPtrList links() const;

    public slots:
        void saveLink(const data_source::LinkDescriptionPtr& description);
        void removeLink(const data_source::LinkDescriptionPtr& description);

    signals:
        void linkAdded(const data_source::LinkDescriptionPtr& description);
        void linkRemoved(const data_source::LinkDescriptionPtr& description);
        void linkChanged(const data_source::LinkDescriptionPtr& description);
        void linkStatisticsChanged(const data_source::LinkDescriptionPtr& description,
                                   int sentBytes, int recvBytes);

    private slots:
        void onLinkStatisticsChanged();

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // COMMUNICATION_MANAGER_H
