#ifndef COMMAND_SERVICE_H
#define COMMAND_SERVICE_H

// Qt
#include <QObject>

// Internal
#include "db_traits.h"

namespace db
{
    class DbFacade;
}

namespace domain
{
    class CommandService: public QObject
    {
        Q_OBJECT

    public:
        explicit CommandService(QObject* parent = nullptr);

    signals:
        void download(db::MissionAssignmentPtr assignment);
        void upload(db::MissionAssignmentPtr assignment);
    };
}

#endif // COMMAND_SERVICE_H
