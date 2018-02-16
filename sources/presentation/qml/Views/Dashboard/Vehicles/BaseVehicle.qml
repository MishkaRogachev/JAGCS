import QtQuick 2.6
import QtPositioning 5.6
import JAGCS 1.0

QtObject {
    id: root
    objectName: "vehicle"

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

    property QtObject mission: QtObject{
        objectName: "mission"

        property int count: 0
        property int current: -1
    }

    property Subsystem ahrs: Subsystem {
        objectName: "ahrs"

        property real pitch: 0.0
        property real roll: 0.0
        property real yaw: 0.0
        property real yawspeed: 0.0

        property var vibration
    }

    property Subsystem battery: Subsystem {
        objectName: "battery"

        property real voltage: 0
        property real current: 0
        property int percentage: 0
    }

    property Subsystem satellite: Subsystem {
        objectName: "satellite"

        property var coordinate: QtPositioning.coordinate()
        property real groundspeed: 0
        property real course: 0
        property int fix: -1
        property int eph: 0
        property int epv: 0
        property int altitude: 0
        property int satellitesVisible: 0
    }

    property Subsystem compass: Subsystem {
        objectName: "compass"

        property real heading: 0.0
    }

    property Subsystem powerSystem: Subsystem {
        objectName: "powerSystem"

        property int throttle: 0
    }
}
