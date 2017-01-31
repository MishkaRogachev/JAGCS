import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import "qrc:/Controls"
import "../../Indicators"

ColumnLayout {
    id: root

    property QtObject vehicle

    RowLayout {

        BatteryIndicator {
            Layout.alignment: Qt.AlignLeft
            charge: vehicle ? vehicle.powerSystem.charge : -1
        }

        Item {
            height: 1
            Layout.fillWidth: true
        }

        GpsIndicator {
            Layout.alignment: Qt.AlignRight
            fix: vehicle ? vehicle.gps.fix : -1
            satellitesVisible: vehicle ? vehicle.gps.satellitesVisible : -1
        }
    }

    ArtificialHorizont {
        width: palette.controlBaseSize * 8

        pitch: vehicle ? vehicle.attitude.pitch : 0.0
        roll: vehicle ? vehicle.attitude.roll : 0.0
        velocity: vehicle ? vehicle.trueAirSpeed : 0.0
        altitude: vehicle ? vehicle.barometricAltitude : 0.0

        rollInverted: parseInt(settings.value("Gui/fdRollInverted"))

        Label {
            anchors.top: parent.top
            anchors.left: parent.left
            text: qsTr("GS") + (vehicle ? Math.round(vehicle.groundSpeed) : 0.0)
        }

        Label {
            anchors.top: parent.top
            anchors.right: parent.right
            text: vehicle ? Math.round(vehicle.gps.coordinate.altitude) : 0.0
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
