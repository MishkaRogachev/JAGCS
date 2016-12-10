import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import "qrc:/Controls"
import "../../Indicators"

ColumnLayout {
    id: root

    property QtObject vehicle

    // TODO: MVP
    FlightDirector {
        id: flightDirector
        Layout.preferredWidth: parent.width

        pitch: vehicle ? vehicle.attitude.pitch : 0.0
        roll: vehicle ? vehicle.attitude.roll : 0.0
        yaw: vehicle ? vehicle.attitude.yaw : 0.0
        velocity: vehicle ? vehicle.trueAirSpeed : 0.0
        altitude: vehicle ? vehicle.barometricAltitude : 0.0
    }

    RowLayout {
        anchors.horizontalCenter: parent.horizontalCenter

        GpsIndicator {
            anchors.verticalCenter: parent.verticalCenter
            fix: vehicle ? vehicle.gps.fix : -1
            satellitesVisible: vehicle ? vehicle.gps.satellitesVisible : -1
        }

        BatteryIndicator {
            anchors.verticalCenter: parent.verticalCenter
            charge: vehicle ? vehicle.powerSystem.charge : -1
        }

        ColumnLayout {
            anchors.verticalCenter: parent.verticalCenter

            Label {
                font.pointSize: 8
                text: qsTr("V:") + " " +
                      (vehicle ? vehicle.powerSystem.voltage.toFixed(2) : "-") +
                      " " + qsTr("v")
            }

            Label {
                font.pointSize: 8
                text: qsTr("C:") + " " +
                      (vehicle ? vehicle.powerSystem.current.toFixed(2) : "-") +
                      " " + qsTr("A")
            }
        }

        // TODO: delay button
        Button {
            text: vehicle && vehicle.armed ? qsTr("DISARM") : qsTr("ARM")
            anchors.verticalCenter: parent.verticalCenter
            onClicked: if (vehicle) vehicle.commandArm(!vehicle.armed)
        }
    }
}
