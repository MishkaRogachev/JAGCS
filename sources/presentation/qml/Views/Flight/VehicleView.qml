import QtQuick 2.6
import QtQuick.Controls 2.0

import "qrc:/Controls"
import "../../Indicators"

Column {
    id: root

    property QtObject vehicle

    ArtificialHorizont {
        width: palette.controlBaseSize * 9

        pitch: vehicle ? vehicle.attitude.pitch : 0.0
        roll: vehicle ? vehicle.attitude.roll : 0.0
        velocity: vehicle ? vehicle.trueAirSpeed : 0.0
        altitude: vehicle ? vehicle.barometricAltitude : 0.0

        rollInverted: parseInt(settings.value("Gui/fdRollInverted"))

        GpsIndicator {
            anchors.top: parent.top
            anchors.right: parent.right
            anchors.margins: 7
            fix: vehicle ? vehicle.gps.fix : -1
            satellitesVisible: vehicle ? vehicle.gps.satellitesVisible : -1
        }

        BatteryIndicator {
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.margins: 7
            charge: vehicle ? vehicle.powerSystem.charge : -1
        }
    }

    Row {
        anchors.horizontalCenter: parent.horizontalCenter

        // TODO: delay button
        Button {
            text: vehicle && vehicle.armed ? qsTr("DISARM") : qsTr("ARM")
            anchors.verticalCenter: parent.verticalCenter
            onClicked: if (vehicle) vehicle.commandArm(!vehicle.armed)
        }
    }
}
