#ifndef MISSION_SERVICE_H
#define MISSION_SERVICE_H

// Qt
#include <QObject>

// Internal
#include "db_traits.h"

namespace db
{
    class DbEntry;
}

namespace domain
{
    class MissionService: public QObject
    {
        Q_OBJECT

    public:
        explicit MissionService(db::DbEntry* entry, QObject* parent = nullptr);
        ~MissionService() override;

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // MISSION_SERVICE_H
