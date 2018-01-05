import QtQuick 2.6
import JAGCS 1.0

import "qrc:/JS/helper.js" as Helper

Item {
    id: vehicleDisplay

    property int vehicleId: 0
    property string vehicleName

    property bool online: false
    property bool armed: false

    property int mode: Domain.None
    property var availableModes: []

    property bool ahrsEnabled: false
    property real pitch: 0.0
    property real roll: 0.0
    property real yaw: 0.0

    property int throttle: 0

    property bool satelliteEnabled: false
    property bool satelliteOperational: false
    property real groundspeed: 0

    property bool barometricEnabled: false
    property bool barometricOperational: false
    property int barometricAltitude: 0
    property real barometricClimb: 0

    property int homeAltitude: 0

    property int speedUnits: settings.value("Gui/fdSpeedUnits")
    property bool altitudeRelative: settings.boolValue("Gui/fdRelativeAltitude")

    // TODO: measured units enum
    property real displayedGroundSpeed: {
        switch (speedUnits) {
        default:
        case 0: return groundspeed;
        case 1: return Helper.mpsToKph(groundspeed);
        }
    }

    property string speedSuffix: {
        switch (speedUnits) {
        default:
        case 0: return qsTr("m/s")
        case 1: return qsTr("km/h")
        }
    }

    property string altitudeSuffix: qsTr("m")

    property real referenceAltitude: 0

    signal updateCommandStatus(var command, var status)

    property QtObject presenter: VehicleDisplayPresenter {
        id: presenter
        view: vehicleDisplay
        Component.onCompleted: setVehicle(vehicleId)
    }
}
