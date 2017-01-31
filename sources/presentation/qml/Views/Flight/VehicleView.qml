import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import "qrc:/Controls"
import "../../Indicators"

ColumnLayout {
    id: root

    property QtObject vehicle

    RowLayout {
        anchors.horizontalCenter: parent.horizontalCenter

        GpsIndicator {
            fix: vehicle ? vehicle.gps.fix : -1
            satellitesVisible: vehicle ? vehicle.gps.satellitesVisible : -1
        }
    }

    FlightDisplay {
        width: palette.controlBaseSize * 8

        pitch: vehicle ? vehicle.attitude.pitch : 0.0
        roll: vehicle ? vehicle.attitude.roll : 0.0
        airSpeed: vehicle ? vehicle.trueAirSpeed : 0.0
        groundSpeed: vehicle ? vehicle.groundSpeed : 0.0
        altitude: vehicle ? vehicle.barometricAltitude : 0.0
        climb: vehicle ? vehicle.barometricClimb : 0.0
        snsAltitude: vehicle ? vehicle.gps.coordinate.altitude : 0.0
        snsFix: vehicle ? vehicle.gps.fix : -1

        rollInverted: parseInt(settings.value("Gui/fdRollInverted"))
    }

    Row {
        anchors.horizontalCenter: parent.horizontalCenter

        BatteryIndicator {
            Layout.alignment: Qt.AlignLeft
            charge: vehicle ? vehicle.powerSystem.charge : -1
        }

        // TODO: delay button
        Button {
            text: vehicle && vehicle.armed ? qsTr("DISARM") : qsTr("ARM")
            anchors.verticalCenter: parent.verticalCenter
            onClicked: if (vehicle) vehicle.commandArm(!vehicle.armed)
        }
    }
}
