#ifndef VEHICLE_H
#define VEHICLE_H

// Internal
#include "command.h"

#include "attitude.h"
#include "position.h"
#include "gps.h"
#include "power_system.h"
#include "wind.h"

namespace domain
{
    class Mission;

    class Vehicle: public QObject // TODO: vehicle hierarchy: Abstract, Land, Aeral, Navy etc
    {
        Q_OBJECT

        Q_PROPERTY(Type type READ type WRITE setType NOTIFY typeChanged)
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

        Q_PROPERTY(bool gpsAvalible READ gpsAvalible
                   WRITE setGpsAvalible NOTIFY gpsAvalibleChanged)
        Q_PROPERTY(Gps gps READ gps WRITE setGps NOTIFY gpsChanged)
        Q_PROPERTY(float groundSpeed READ groundSpeed WRITE setGroundSpeed
                   NOTIFY groundSpeedChanged)

        Q_PROPERTY(PowerSystem powerSystem READ powerSystem
                   WRITE setPowerSystem NOTIFY powerSystemChanged)

        Q_PROPERTY(bool airSpeedAvalible READ airSpeedAvalible
                   WRITE setAirSpeedAvalible NOTIFY airSpeedAvalibleChanged)
        Q_PROPERTY(float indicatedAirSpeed READ indicatedAirSpeed
                   WRITE setIndicatedAirSpeed NOTIFY indicatedAirSpeedChanged)
        Q_PROPERTY(float trueAirSpeed READ trueAirSpeed WRITE setTrueAirSpeed
                   NOTIFY trueAirSpeedChanged)
        Q_PROPERTY(Wind wind READ wind WRITE setWind NOTIFY windChanged)

        Q_PROPERTY(bool barometerAvalible READ barometerAvalible
                   WRITE setBarometerAvalible NOTIFY barometerAvalibleChanged)
        Q_PROPERTY(float barometricAltitude READ barometricAltitude
                   WRITE setBarometricAltitude NOTIFY barometricAltitudeChanged)
        Q_PROPERTY(float barometricClimb READ barometricClimb
                   WRITE setBarometricClimb NOTIFY barometricClimbChanged)

        Q_PROPERTY(bool compasAvalible READ compasAvalible
                   WRITE setCompasAvalible NOTIFY compasAvalibleChanged)
        Q_PROPERTY(int heading READ heading WRITE setHeading
                   NOTIFY headingChanged)

        Q_PROPERTY(bool rangeFinderAvalible READ rangeFinderAvalible
                   WRITE setRangeFinderAvalible NOTIFY rangeFinderAvalibleChanged)

        Q_PROPERTY(bool ahrsAvalible READ ahrsAvalible
                   WRITE setAhrsAvalible NOTIFY ahrsAvalibleChanged)

    public:
        enum Type
        {
            UnknownType = 0,
            FixedWingAircraft
        };

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

        Vehicle(uint8_t vehicleId, QObject* parent);
        ~Vehicle() override;

        uint8_t vehicleId() const;

        Type type() const;
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

        bool gpsAvalible() const;
        Gps gps() const;
        float groundSpeed() const;

        PowerSystem powerSystem() const;

        bool airSpeedAvalible() const;
        float indicatedAirSpeed() const;
        float trueAirSpeed() const;
        Wind wind() const;

        bool barometerAvalible() const;
        float barometricAltitude() const;
        float barometricClimb() const;

        bool compasAvalible() const;
        int heading() const;

        bool rangeFinderAvalible() const;

        bool ahrsAvalible() const;

        Mission* assignedMission() const;

    public slots:
        void setType(Type type);
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

        void setPowerSystem(const PowerSystem& powerSystem);

        void setAirSpeedAvalible(bool airSpeedAvalible);
        void setIndicatedAirSpeed(float indicatedAirSpeed);
        void setTrueAirSpeed(float trueAirSpeed);
        void setWind(Wind wind);

        void setBarometerAvalible(bool barometerAvalible);
        void setBarometricAltitude(float barometricAltitude);
        void setBarometricClimb(float barometricClimb);

        void setCompasAvalible(bool compasAvalible);
        void setHeading(int heading);

        void setRangeFinderAvalible(bool rangeFinderAvalible);

        void setAhrsAvalible(bool ahrsAvalible);

        void assignMission(Mission* mission);
        void unassignMission();

    signals:
        void typeChanged(Type type);
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

        void gpsAvalibleChanged(bool gpsAvalible);
        void gpsChanged(Gps gps);
        void groundSpeedChanged(float groundSpeed);

        void powerSystemChanged(PowerSystem powerSystem);

        void airSpeedAvalibleChanged(bool airSpeedAvalible);
        void indicatedAirSpeedChanged(float indicatedAirSpeed);
        void trueAirSpeedChanged(float trueAirSpeed);
        void windChanged(Wind wind);

        void barometerAvalibleChanged(bool barometerAvalible);
        void barometricAltitudeChanged(float barometricAltitude);
        void barometricClimbChanged(float barometricClimb);

        void compasAvalibleChanged(bool compasAvalible);
        void headingChanged(int heading);

        void rangeFinderAvalibleChanged(bool rangeFinderAvalible);

        void ahrsAvalibleChanged(bool ahrsAvalible);

        void assignedMissionChanged(Mission* mission);

        void executeCommand(Command command, const QVariantList& args);
        void sendHomePositionSetting(const Position& homePosition);

    private:
        uint8_t m_vehicleId;

        Type m_type;
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

        PowerSystem m_powerSystem;

        bool m_airSpeedAvalible;
        float m_indicatedAirSpeed;
        float m_trueAirSpeed;
        Wind m_wind;

        bool m_barometerAvalible;
        float m_barometricAltitude;
        float m_barometricClimb;

        bool m_compasAvalible;
        int m_heading;

        bool m_rangeFinderAvalible;

        bool m_ahrsAvalible;

        Mission* m_assignedMission;

        Q_ENUM(Type)
        Q_ENUM(State)
    };
}

#endif // VEHICLE_H
