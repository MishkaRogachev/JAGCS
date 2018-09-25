import QtQuick 2.6
import JAGCS 1.0

BaseVehicle {
    id: root

    property Subsystem barometric: Subsystem {
        objectName: "barometric"

        property real altitude: NaN
        property real climb: NaN

        readonly property real displayedAltitude: dashboard.altitudeRelative ?
                                                      altitude - home.altitude : altitude

        function fromDisplayedAltitude(displayedAltitude) {
            return dashboard.altitudeRelative ?
                        displayedAltitude : displayedAltitude - home.altitude;
        }
    }

    property Subsystem pitot: Subsystem {
        objectName: "pitot"

        property real indicatedAirspeed: NaN
        property real trueAirspeed: NaN
    }

    property QtObject ekf: QtObject {
        objectName: "ekf"

        property real velocityVariance: NaN
        property real verticalVariance: NaN
        property real horizontVariance: NaN
        property real compassVariance: NaN
        property real terrainAltitudeVariance: NaN
    }

    property Subsystem radalt: Subsystem {
        objectName: "radalt"

        property real altitude: NaN
    }

    property QtObject flightControl: QtObject {
        objectName: "flightControl"

        property real desiredPitch: NaN
        property real desiredRoll: NaN
        property real desiredHeading: NaN
        property real airspeedError: NaN
        property real altitudeError: NaN
    }

    property QtObject navigator: QtObject {
        objectName: "navigator"

        property real targetBearing: NaN
        property real trackError: NaN
        property int targetDistance: 0
    }

    property QtObject landingSystem: QtObject {
        objectName: "landingSystem"

        property int distance: 0
        property real deviationX: NaN
        property real deviationY: NaN
        property real sizeX: NaN
        property real sizeY: NaN
    }

    property QtObject wind: QtObject {
        objectName: "wind"

        property real direction: NaN
        property real speed: NaN
    }
}
