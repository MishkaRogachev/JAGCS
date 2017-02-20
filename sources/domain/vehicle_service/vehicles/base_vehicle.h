#ifndef BASE_VEHICLE_H
#define BASE_VEHICLE_H

// Internal
#include "abstract_vehicle.h"

#include "attitude.h"
#include "position.h"
#include "gps.h"
#include "power_system.h"

namespace domain
{
    class BaseVehicle: public AbstractVehicle
    {
        Q_OBJECT

        Q_PROPERTY(State state READ state WRITE setState NOTIFY stateChanged)

        Q_PROPERTY(bool armed READ isArmed WRITE setArmed NOTIFY armedChanged)
        Q_PROPERTY(bool autonomous READ autonomous WRITE setAutonomous
                   NOTIFY autonomousChanged)
        Q_PROPERTY(bool guided READ guided WRITE setGuided NOTIFY guidedChanged)
        Q_PROPERTY(bool stabilized READ stabilized WRITE setStabilized
                   NOTIFY stabilizedChanged)

        Q_PROPERTY(bool insAvalible READ insAvalible
                   WRITE setInsAvalible NOTIFY insAvalibleChanged)
        Q_PROPERTY(Attitude attitude READ attitude WRITE setAttitude
                   NOTIFY attitudeChanged)

        Q_PROPERTY(Position position READ position WRITE setPosition
                   NOTIFY positionChanged)
        Q_PROPERTY(Position homePosition READ homePosition
                   WRITE setHomePosition NOTIFY homePositionChanged)
        Q_PROPERTY(float homeDirection READ homeDirection
                   NOTIFY homeDirectionChanged)
        Q_PROPERTY(float homeDistance READ homeDistance
                   NOTIFY homeDistanceChanged)
        Q_PROPERTY(float missionDirection READ missionDirection
                   NOTIFY missionDirectionChanged)
        Q_PROPERTY(float missionDistance READ missionDistance
                   NOTIFY missionDistanceChanged)

        Q_PROPERTY(bool gpsAvalible READ gpsAvalible
                   WRITE setGpsAvalible NOTIFY gpsAvalibleChanged)
        Q_PROPERTY(Gps gps READ gps WRITE setGps NOTIFY gpsChanged)
        Q_PROPERTY(float groundSpeed READ groundSpeed WRITE setGroundSpeed
                   NOTIFY groundSpeedChanged)

        Q_PROPERTY(int throttle READ throttle WRITE setThrottle
                   NOTIFY throttleChanged)
        Q_PROPERTY(PowerSystem powerSystem READ powerSystem
                   WRITE setPowerSystem NOTIFY powerSystemChanged)

        Q_PROPERTY(bool compasAvalible READ compasAvalible
                   WRITE setCompasAvalible NOTIFY compasAvalibleChanged)
        Q_PROPERTY(int heading READ heading WRITE setHeading
                   NOTIFY headingChanged)

    public:
        enum State
        {
            UnknownState = 0,
            Boot,
            Calibrating,
            Standby,
            Active,
            Critical,
            Emergency,
            PowerOff
        };

        BaseVehicle(uint8_t vehicleId, int type, QObject* parent);

        State state() const;

        bool isArmed() const;
        bool autonomous() const;
        bool guided() const;
        bool stabilized() const;

        bool insAvalible() const;
        Attitude attitude() const;

        Position position() const;
        Position homePosition() const;
        float homeDirection() const;
        float homeDistance() const;
        float missionDirection() const;
        float missionDistance() const;

        bool gpsAvalible() const;
        Gps gps() const;
        float groundSpeed() const;

        int throttle() const;
        PowerSystem powerSystem() const;

        bool compasAvalible() const;
        int heading() const;

    public slots:
        void setState(State state);

        void setArmed(bool armed);
        void setAutonomous(bool autonomous);
        void setGuided(bool guided);
        void setStabilized(bool stabilized);

        void setInsAvalible(bool insAvalible);
        void setAttitude(const Attitude& attitude);

        void setPosition(const Position& position);
        void setHomePosition(const Position& homePosition);

        void setGpsAvalible(bool gpsAvalible);
        void setGps(const Gps& gps);
        void setGroundSpeed(float groundSpeed);

        void setThrottle(int throttle);
        void setPowerSystem(const PowerSystem& powerSystem);

        void setCompasAvalible(bool compasAvalible);
        void setHeading(int heading);

    signals:
        void stateChanged(State state);

        void armedChanged(bool armed);
        void autonomousChanged(bool autonomous);
        void guidedChanged(bool guided);
        void stabilizedChanged(bool stabilized);

        void insAvalibleChanged(bool insAvalible);
        void attitudeChanged(Attitude attitude);

        void positionChanged(Position position);
        void homePositionChanged(Position homePosition);
        void homeDirectionChanged(float homeDirection);
        void homeDistanceChanged(float homeDistance);
        void missionDirectionChanged(float missionDirection);
        void missionDistanceChanged(float missionDistance);

        void gpsAvalibleChanged(bool gpsAvalible);
        void gpsChanged(Gps gps);
        void groundSpeedChanged(float groundSpeed);

        void throttleChanged(int throttle);
        void powerSystemChanged(PowerSystem powerSystem);

        void compasAvalibleChanged(bool compasAvalible);
        void headingChanged(int heading);

        void sendHomePositionSetting(const Position& homePosition);

    private:
        State m_state;

        bool m_armed;
        bool m_autonomous;
        bool m_guided;
        bool m_stabilized;

        bool m_insAvalible;
        Attitude m_attitude;

        Position m_position;
        Position m_homePosition;

        bool m_gpsAvalible;
        Gps m_gps;
        float m_groundSpeed;

        int m_throttle;
        PowerSystem m_powerSystem;

        bool m_compasAvalible;
        int m_heading;

        Q_ENUM(State)
    };
}

#endif // BASE_VEHICLE_H
