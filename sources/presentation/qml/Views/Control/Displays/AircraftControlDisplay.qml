import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

GridLayout {
    id: root

    property int waypoint: 0
    property alias waypoints: waypointBox.model
    property bool armed: false
    property bool guided: false

    property int groundspeed: 0
    property int indicatedAirspeed: 0

    signal commandSetWaypoint(int item)

    signal commandStatusChanged(var command, var status)
    signal executeCommand(int command, var arguments)
    signal rejectCommand(int command)

    onWaypointChanged: waypointBox.currentIndex = waypointBox.model.indexOf(waypoint.toString())
    columns: 4

    Controls.CommandSwitch { // FIXME: dangerous switch
        command: Command.ArmDisarm
        text: armed ? qsTr("DISARM") : qsTr("ARM")
        inputChecked: armed
        font.pixelSize: palette.fontPixelSize * 0.75
        font.bold: true
        Layout.fillWidth: true
        Layout.columnSpan: 2
    }

//    Controls.CommandButton {
//        command: Command.Takeoff
//        iconSource: "qrc:/icons/takeoff.svg"
//        Layout.alignment: Qt.AlignRight
//    }

    Controls.CommandButton {
        command: Command.Land
        iconSource: "qrc:/icons/landing.svg"
    }

    Controls.CommandButton {
        command: Command.GoAround
        iconSource: "qrc:/icons/go_around.svg"
    }

    Controls.Label {
        text: qsTr("Waypoint:")
        font.pixelSize: palette.fontPixelSize * 0.75
        font.bold: true
    }

    Controls.ComboBox {
        id: waypointBox
        model: []
        onCurrentTextChanged: commandSetWaypoint(currentText)
        enabled: guided
        Layout.fillWidth: true
    }

    Controls.CommandButton {
        command: Command.Return
        iconSource: "qrc:/icons/home.svg"
    }

    Controls.CommandButton {
        command: Command.Start
        iconSource: "qrc:/icons/play.svg"
    }

    Controls.Label {
        text: qsTr("Speed:")
        font.pixelSize: palette.fontPixelSize * 0.75
        font.bold: true
    }

    Controls.SpinBox {
        id: speedBox
        Layout.fillWidth: true
    }

    Controls.Button {
        iconSource: "qrc:/icons/restore.svg"
        onClicked: speedBox.value = indicatedAirspeed
    }

    Controls.CommandButton {
        command: Command.SetSpeed
        iconSource: "qrc:/icons/right.svg"
        args: [0, speedBox.value, -1, 0] // TODO: groundspeed
        enabled: guided
    }
}
