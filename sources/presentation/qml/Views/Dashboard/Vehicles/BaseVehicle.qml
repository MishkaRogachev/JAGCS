import QtQuick 2.6
import QtPositioning 5.6
import JAGCS 1.0

import "qrc:/JS/helper.js" as Helper

QtObject {
    id: root
    objectName: "vehicle"

    property int vehicleId: 0
    property string vehicleName
    property int vehicleType: Vehicle.UnknownType

    property int vehicleState: Domain.UnknownState
    property bool online: false
    property bool armed: false
    property bool guided: false

    property int mode: Domain.None
    property var availableModes: []

    property var position: QtPositioning.coordinate()
    property var homePosition: QtPositioning.coordinate()

    property int speedUnits: settings.value("Gui/fdSpeedUnits")
    property bool altitudeRelative: settings.boolValue("Gui/fdRelativeAltitude")

    // TODO: measured units enum
    property string speedSuffix: {
        switch (speedUnits) {
        default:
        case 0: return qsTr("m/s")
        case 1: return qsTr("km/h")
        }
    }

    // TODO: altitude units
    property string altitudeSuffix: qsTr("m")

    QtObject {
        id: mission
        objectName: "mission"

        property int count: 0
        property int current: -1
    }

    Subsystem {
        id: ahrs
        objectName: "ahrs"

        property real pitch: 0.0
        property real roll: 0.0
        property real yaw: 0.0
        property real yawspeed: 0.0

        property var vibration

        QtObject {
            id: ekf
            objectName: "ekf"

            property real velocityVariance: 0.0
            property real verticalVariance: 0.0
            property real horizontVariance: 0.0
            property real compassVariance: 0.0
            property real terrainAltitudeVariance: 0.0
        }
    }

    Subsystem {
        id: battery
        objectName: "battery"

        property real voltage: 0
        property real current: 0
        property int percentage: 0
    }

    Subsystem {
        id: satellite
        objectName: "satellite"

        property var coordinate: QtPositioning.coordinate()
        property real groundspeed: 0
        property real course: 0
        property int fix: -1
        property int eph: 0
        property int epv: 0
        property int altitude: 0
        property int satellitesVisible: 0

        readonly property real displayedGroundSpeed: {
            switch (speedUnits) {
            default:
            case 0: return groundspeed;
            case 1: return Helper.mpsToKph(groundspeed);
            }
        }
    }

    Subsystem {
        id: compass
        objectName: "compass"

        property real heading: 0.0
    }

    Subsystem {
        id: powerSystem
        objectName: "powerSystem"

        property int throttle: 0
    }
}
