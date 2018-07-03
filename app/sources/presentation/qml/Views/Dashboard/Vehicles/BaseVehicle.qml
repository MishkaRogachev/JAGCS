import QtQuick 2.6
import QtPositioning 5.6
import JAGCS 1.0

QtObject {
    id: root
    objectName: "vehicle"

    property string vehicleName
    property int vehicleType: Vehicle.UnknownType

    property bool online: false
    property bool armed: false
    property bool guided: false
    property bool stab: false
    property int vehicleState: Domain.UnknownState

    property int mode: Domain.None
    property var availableModes: []

    property variant position: QtPositioning.coordinate()

    property QtObject home: QtObject{
        objectName: "home"

        property variant position: QtPositioning.coordinate()
        property real altitude: NaN
    }

    property QtObject mission: QtObject{
        objectName: "mission"

        property bool assigned: false
        property int status: MissionAssignment.NotActual

        property int count: 0
        property int current: -1
    }

    property Subsystem ahrs: Subsystem {
        objectName: "ahrs"

        property real pitch: NaN
        property real roll: NaN
        property real yaw: NaN
        property real yawspeed: NaN

        property var vibration
    }

    property Subsystem battery: Subsystem {
        objectName: "battery"

        property real voltage: NaN
        property real current: NaN
        property int percentage: 0
    }

    property Subsystem satellite: Subsystem {
        objectName: "satellite"

        property var coordinate: QtPositioning.coordinate()
        property real groundspeed: NaN
        property real course: NaN
        property real altitude: NaN
        property int fix: -1
        property int eph: 0
        property int epv: 0
        property int satellitesVisible: 0
    }

    property Subsystem compass: Subsystem {
        objectName: "compass"

        property real heading: NaN
    }

    property Subsystem powerSystem: Subsystem {
        objectName: "powerSystem"

        property int throttle: 0
    }
}
