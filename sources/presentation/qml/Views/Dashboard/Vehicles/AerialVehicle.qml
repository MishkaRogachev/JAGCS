import QtQuick 2.6
import JAGCS 1.0

BaseVehicle {
    id: root

    property Subsystem barometric: Subsystem {
        objectName: "barometric"

        property int altitude: 0
        property real climb: 0

        readonly property real displayedAltitude: {
            return units.convertDistance(altitudeUnits,
                                         altitudeRelative && homePosition.isValid ?
                                             altitude - homePosition.altitude : altitude);
        }

        function fromDisplayedAltitude(alt) {
            return altitudeRelative && homePosition.isValid ? alt + homePosition.altitude : alt;
        }
    }

    property Subsystem pitot: Subsystem {
        objectName: "pitot"

        property real indicatedAirspeed: 0.0
        property real trueAirspeed: 0.0

        readonly property real displayedIndicatedAirspeed: units.convertSpeed(speedUnits, indicatedAirspeed)
        readonly property real displayedTrueAirspeed: units.convertSpeed(speedUnits, trueAirspeed)
    }

    property QtObject ekf: QtObject {
        objectName: "ekf"

        property real velocityVariance: 0.0
        property real verticalVariance: 0.0
        property real horizontVariance: 0.0
        property real compassVariance: 0.0
        property real terrainAltitudeVariance: 0.0
    }

    property Subsystem radalt: Subsystem {
        objectName: "radalt"

        property real altitude: 0
    }

    property QtObject flightControl: QtObject {
        objectName: "flightControl"

        property real desiredPitch: 0.0
        property real desiredRoll: 0.0
        property real desiredHeading: 0.0
        property real airspeedError: 0.0
        property real altitudeError: 0.0

        readonly property real displayedAirspeedError: units.convertSpeed(speedUnits, airspeedError)
    }

    property QtObject navigator: QtObject {
        objectName: "navigator"

        property real targetBearing: 0.0
        property real trackError: 0.0
        property int targetDistance: 0
    }

    property QtObject wind: QtObject {
        objectName: "wind"

        property real direction: 0
        property real speed: 0

        readonly property real displayedSpeed: units.convertSpeed(speedUnits, speed)
    }
}
