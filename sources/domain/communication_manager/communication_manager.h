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

namespace domain
{
    class ICommunicatorFactory;

    class CommunicationManager: public QObject
    {
        Q_OBJECT

    public:
        CommunicationManager(ICommunicatorFactory* commFactory,
                             data_source::DbEntry* entry,
                             QObject* parent = nullptr);
        ~CommunicationManager() override;

    public slots:
        void addLink(const data_source::LinkDescriptionPtr& description);

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // COMMUNICATION_MANAGER_H
