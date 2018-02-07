import QtQuick 2.6
import JAGCS 1.0

import "qrc:/JS/helper.js" as Helper

BaseVehicle {
    id: root

    property Subsystem barometric: Subsystem {
        objectName: "barometric"

        property int altitude: 0
        property real climb: 0

        readonly property real displayedAltitude: {
            return altitudeRelative ? altitude - homePosition.altitude : altitude;
        }
    }

    property Subsystem pitot: Subsystem {
        objectName: "pitot"

        property real indicatedAirspeed: 0.0
        property real trueAirspeed: 0.0

        readonly property real displayedIndicatedAirspeed: {
            switch (speedUnits) {
            default:
            case 0: return indicatedAirspeed;
            case 1: return Helper.mpsToKph(indicatedAirspeed);
            }
        }

        readonly property real displayedTrueAirspeed: {
            switch (speedUnits) {
            default:
            case 0: return trueAirspeed;
            case 1: return Helper.mpsToKph(trueAirspeed);
            }
        }
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

        readonly property real displayedAirspeedError: {
            switch (speedUnits) {
            default:
            case 0: return airspeedError;
            case 1: return Helper.mpsToKph(airspeedError);
            }
        }
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

        readonly property real displayedSpeed: {
            switch (speedUnits) {
            default:
            case 0: return speed;
            case 1: return Helper.mpsToKph(speed);
            }
        }
    }
}
