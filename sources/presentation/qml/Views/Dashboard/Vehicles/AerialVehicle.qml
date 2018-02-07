import QtQuick 2.6
import JAGCS 1.0

import "qrc:/JS/helper.js" as Helper

BaseVehicle {
    id: root

    Subsystem {
        id: barometric
        objectName: "barometric"

        property int altitude: 0
        property real climb: 0
    }

    Subsystem {
        id: pitot
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

    Subsystem {
        id: radalt
        objectName: "radalt"

        property real altitude: 0
    }

    QtObject {
        id: flightControl
        objectName: "flightControl"

        property real desiredPitch: 0.0
        property real desiredRoll: 0.0
        property real desiredHeading: 0.0
    }

    QtObject {
        id: navigator
        objectName: "navigator"

        property real targetBearing: 0.0
        property real trackError: 0.0
        property real airspeedError: 0.0
        property real altitudeError: 0.0
        property int targetDistance: 0

        readonly property real displayedAirspeedError: {
            switch (speedUnits) {
            default:
            case 0: return airspeedError;
            case 1: return Helper.mpsToKph(airspeedError);
            }
        }
    }

    QtObject {
        id: wind
        objectName: "wind"

        property real windDirection: 0
        property real windSpeed: 0

        readonly property real displayedWindSpeed: {
            switch (speedUnits) {
            default:
            case 0: return windSpeed;
            case 1: return Helper.mpsToKph(windSpeed);
            }
        }
    }
}
