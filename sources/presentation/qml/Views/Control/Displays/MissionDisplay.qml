import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

RowLayout {
    id: root

    property int waypoint: 0
    property alias waypoints: waypointBox.model
    property bool guided: false

    signal commandSetWaypoint(int item)

    signal commandStatusChanged(var command, var status)
    signal executeCommand(int command)
    signal executeBoolCommand(int command, bool check)
    signal rejectCommand(int command)

    onWaypointChanged: waypointBox.currentIndex = waypointBox.model.indexOf(waypoint.toString())

    Controls.Label {
        text: qsTr("WP: ")
        font.pixelSize: palette.fontPixelSize * 0.75
        font.bold: true
    }

    Controls.ComboBox {
        id: waypointBox
        model: []
        onCurrentTextChanged: commandSetWaypoint(currentText)
        implicitWidth: palette.controlBaseSize * 2
        enabled: guided
    }

    Item {
        Layout.fillWidth: true
    }

    GridLayout {
        columns: 3

        Controls.CommandButton {
            command: Command.Takeoff
            iconSource: "qrc:/icons/takeoff.svg"
        }

        Controls.CommandButton {
            command: Command.Land
            iconSource: "qrc:/icons/landing.svg"
        }

        Controls.CommandButton {
            command: Command.GoAround
            iconSource: "qrc:/icons/go_around.svg"
        }

        Controls.CommandButton {
            command: Command.Return
            iconSource: "qrc:/icons/home.svg"
        }

        Controls.CommandButton {
            command: Command.Start
            iconSource: "qrc:/icons/play.svg"
        }


    }
}
