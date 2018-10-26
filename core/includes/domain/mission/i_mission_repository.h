#ifndef I_MISSION_REPOSITORY_H
#define I_MISSION_REPOSITORY_H

// Qt
#include <QObject>

// Internal
#include "dto_traits.h"

namespace data_source
{
    class IMissionRepository: public QObject
    {
        Q_OBJECT

    public:
        explicit IMissionRepository(QObject* parent): QObject(parent) {}

        virtual dto::MissionPtrList missions() = 0;

    public slots:
        virtual bool save(const dto::MissionPtr& mission) = 0;
        virtual bool remove(const dto::MissionPtr& mission) = 0;

    signals:
        void missionAdded(dto::MissionPtr mission);
        void missionRemoved(dto::MissionPtr mission);
        void missionChanged(dto::MissionPtr mission);

    };
}

#endif // I_MISSION_REPOSITORY_H
