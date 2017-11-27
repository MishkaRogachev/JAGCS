#ifndef MISSION_ASSIGNMENT_H
#define MISSION_ASSIGNMENT_H

// Internal
#include "base_dao.h"

// Qt
#include <QVector>

namespace dao
{
    class MissionAssignment: public BaseDao
    {
        Q_GADGET

        Q_PROPERTY(int missionId READ missionId WRITE setMissionId)
        Q_PROPERTY(int vehicleId READ vehicleId WRITE setVehicleId)
        Q_PROPERTY(Status status READ status WRITE setStatus)
        Q_PROPERTY(int progress READ progress WRITE setProgress)

    public:
        enum Status: quint8
        {
            NotActual = 0,
            Downloading,
            Uploading,
            Actual
        };

        int missionId() const;
        void setMissionId(int missionId);

        int vehicleId() const;
        void setVehicleId(int vehicleId);

        Status status() const;
        void setStatus(Status status);

        int progress() const;
        void setProgress(int progress);
        void addProgress();

    private:
        int m_missionId = 0;
        int m_vehicleId = 0;

        Status m_status = NotActual;
        int m_progress = 0;

        Q_ENUM(Status)
    };
}

#endif // MISSION_ASSIGNMENT_H
