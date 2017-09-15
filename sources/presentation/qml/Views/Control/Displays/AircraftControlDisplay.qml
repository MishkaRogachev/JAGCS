import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

BaseDisplay {
    id: root

    property int waypoint: 0
    property alias waypoints: waypointBox.model

    property bool armed: false
    property bool guided: false
    property bool downloading: false

    property int groundspeed: 0
    property int indicatedAirspeed: 0
    property int command: commandBox.currentItem ? commandBox.currentItem.command : Command.UnknownCommand

    signal commandSetWaypoint(int item)
    signal downloadMission()
    signal cancelSyncMission()

    signal commandStatusChanged(var command, var status)
    signal executeCommand(int command, var arguments)
    signal rejectCommand(int command)

    onWaypointChanged: waypointBox.currentIndex = waypointBox.model.indexOf(waypoint.toString())

    implicitHeight: palette.controlBaseSize * 6
    implicitWidth: grid.width

    GridLayout {
        id: grid
        anchors.top: parent.top
        columns: 3

        Controls.Label {
            text: qsTr("WP:")
            font.pixelSize: palette.fontPixelSize * 0.75
            font.bold: true
            Layout.fillWidth: true
        }

        Controls.ComboBox {
            id: waypointBox
            model: []
            onCurrentTextChanged: commandSetWaypoint(currentText)
            enabled: guided
            Layout.fillWidth: true
        }

        Controls.Button {
            iconSource: "qrc:/icons/download.svg"
            highlighted: downloading
            onClicked: highlighted ? cancelSyncMission() : downloadMission()
        }

        Controls.Label {
            text: qsTr("Command:")
            font.pixelSize: palette.fontPixelSize * 0.75
            font.bold: true
        }

        Controls.ComboBox {
            id: commandBox
            model: [
                { icon: "", text: "", command: Command.UnknownCommand },
                { icon: "qrc:/icons/calibrate.svg", text: qsTr("Preflight"),
                    command: Command.PreflightCalibration},
                { icon: armed ? "qrc:/icons/unlock.svg" : "qrc:/icons/lock.svg",
                                text: armed ? qsTr("Disarm") : qsTr("Arm"), command: Command.ArmDisarm },
                { icon: "qrc:/icons/home.svg", text: qsTr("Return"), command: Command.Return },
                { icon: "qrc:/icons/play.svg", text: qsTr("Start mission"), command: Command.Start },
                { icon: "qrc:/icons/landing.svg", text: qsTr("Land"), command: Command.Land },
                { icon: "qrc:/icons/go_around.svg", text: qsTr("Go around"), command: Command.GoAround },
                { icon: "qrc:/icons/speed.svg", text: qsTr("Set airspeed"), command: Command.SetSpeed, type: 0 },
                { icon: "qrc:/icons/speed.svg", text: qsTr("Set groundspeed"), command: Command.SetSpeed, type: 1 },
                { icon: "qrc:/icons/home.svg", text: qsTr("Set home"), command: Command.SetHome },
            ]
            Layout.fillWidth: true
        }

        Controls.CommandButton {
            command: root.command
            iconSource: "qrc:/icons/right.svg"
            enabled: commandBox.currentIndex > 0
            args: {
                switch (command) {
                case Command.PreflightCalibration: return calibrationBox.currentItem.args;
                case Command.ArmDisarm: return [!armed];
                case Command.SetSpeed: return [commandBox.currentItem.type, speedBox.value, -1, 0];
                case Command.SetHome: return [2, 0, 0, 0, latitudeBox.realValue,
                                              longitudeBox.realValue, altitudeBox.value]; // TODO: current
                default: return [];
                }
            }
        }

        Controls.Label {
            text: qsTr("Altitude:")
            font.pixelSize: palette.fontPixelSize * 0.75
            font.bold: true
            visible: command === Command.SetHome
        }

        Controls.SpinBox {
            id: altitudeBox
            visible: command === Command.SetHome
            to: 20000 // TODO: borderValues
            Layout.fillWidth: true
            Layout.columnSpan: 2
        }

        Controls.Label {
            text: qsTr("Latitude")
            visible: command === Command.SetHome
            Layout.fillWidth: true
        }

        Controls.CoordSpinBox {
            id: latitudeBox
            visible: command === Command.SetHome
            Layout.fillWidth: true
        }

        Controls.MapPickButton {
            id: pickButton
            visible: command === Command.SetHome
            Layout.rowSpan: 2
            onPicked: {
                latitudeBox.realValue = coordinate.latitude;
                longitudeBox.realValue = coordinate.longitude;
            }
            onVisibleChanged: {
                map.dropPicker()
                picking = false;
            }
        }

        Controls.Label {
            text: qsTr("Longitude")
            visible: command === Command.SetHome
            Layout.fillWidth: true
        }

        Controls.CoordSpinBox {
            id: longitudeBox
            visible: command === Command.SetHome
            isLongitude: true
            Layout.fillWidth: true
        }

        Controls.Label {
            text: qsTr("Speed:")
            font.pixelSize: palette.fontPixelSize * 0.75
            font.bold: true
            visible: command === Command.SetSpeed
        }

        Controls.SpinBox {
            id: speedBox
            visible: command === Command.SetSpeed
            to: 999 // TODO: borderValues
            Layout.fillWidth: true
        }

        Controls.Button {
            iconSource: "qrc:/icons/restore.svg"
            onClicked: speedBox.value = commandBox.currentItem.type ? groundspeed : indicatedAirspeed
            visible: command === Command.SetSpeed
        }

        Controls.Label {
            text: qsTr("Calibration:")
            font.pixelSize: palette.fontPixelSize * 0.75
            font.bold: true
            visible: command === Command.PreflightCalibration
        }

        Controls.ComboBox {
            id: calibrationBox
            visible: command === Command.PreflightCalibration
            model: [
                { text: qsTr("Accelerometer"), args: [0, 0, 0, 0, 1, 0, 0 ] },
                { text: qsTr("Board level"), args: [0, 0, 0, 0, 2, 0, 0 ] },
                { text: qsTr("Gyroscope"), args: [1, 0, 0, 0, 0, 0, 0 ] },
                { text: qsTr("Magnetometer"), args: [0, 1, 0, 0, 0, 0, 0 ] },
                { text: qsTr("Static pressure"), args: [0, 0, 1, 0, 0, 0, 0 ] },
                { text: qsTr("Temperature"), args: [3, 0, 0, 0, 3, 0, 3 ] },
            ]
            Layout.fillWidth: true
            Layout.columnSpan: 2
        }
    }
}
