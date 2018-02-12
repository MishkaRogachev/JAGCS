import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls
import "../CommandControls" as CommandControls

Controls.Pane {
    id: root

    Connections {
        target: vehicleDisplay
        onUpdateCommandStatus: {
            switch (command) {
            case Command.ArmDisarm:
                armDisarm.status = status;
                break;
            case Command.SetMode:
                modeBox.status = status;
                break;
            case Command.Return:
                rtl.status = status;
                break;
            case sendButton.command:
                sendButton.status = status;
                break;
            default:
                break;
            }
        }
    }

    enabled: vehicle.online

    GridLayout {
        anchors.centerIn: parent
        width: parent.width
        rowSpacing: sizings.spacing
        columnSpacing: sizings.spacing
        columns: 3

        CommandControls.DelayButton {
            id: armDisarm
            text: vehicle.armed ? qsTr("DISARM") : qsTr("ARM")
            args: [ !vehicle.armed ]
            command: Command.ArmDisarm
            Layout.preferredWidth: sizings.controlBaseSize * 2
        }

        CommandControls.ModeBox {
            id: modeBox
            mode: vehicle.mode
            model: vehicle.availableModes
            Layout.fillWidth: true
        }

        CommandControls.Button {
            id: rtl
            tipText: qsTr("Return to launch")
            iconSource: "qrc:/icons/home.svg"
            command: Command.Return
            Layout.alignment: Qt.AlignRight
        }

        Controls.Label {
            text: qsTr("Command")
            font.pixelSize: sizings.fontPixelSize * 0.7
            font.bold: true
        }

        Controls.ComboBox {
            id: commandBox
            model: [
                { icon: "", text: "", command: Command.UnknownCommand },
                { icon: "qrc:/icons/calibrate.svg", text: qsTr("Preflight"), command: Command.PreflightCalibration},
                { icon: "qrc:/icons/play.svg", text: qsTr("Start mission"), command: Command.Start },
                { icon: "qrc:/icons/landing.svg", text: qsTr("Land"), command: Command.Land },
                { icon: "qrc:/icons/go_around.svg", text: qsTr("Go around"), command: Command.GoAround },
                { icon: "qrc:/icons/center.svg", text: qsTr("Nav to"), command: Command.NavTo },
                { icon: "qrc:/icons/speed.svg", text: qsTr("Set airspeed"), command: Command.SetSpeed, type: 0 },
                { icon: "qrc:/icons/speed.svg", text: qsTr("Set groundspeed"), command: Command.SetSpeed, type: 1 },
                { icon: "qrc:/icons/up.svg", text: qsTr("Set altitude"), command: Command.SetAltitude },
                { icon: "qrc:/icons/home.svg", text: qsTr("Set home"), command: Command.SetHome },
            ]
            Layout.fillWidth: true
        }

        CommandControls.Button {
            id: sendButton
            command: commandBox.currentItem ? commandBox.currentItem.command : Command.UnknownCommand
            iconSource: "qrc:/icons/right.svg"
            enabled: commandBox.currentIndex > 0
            args: {
                switch (command) {
                case Command.PreflightCalibration:
                    return calibrationBox.currentItem.args;
                case Command.NavTo:
                    return [latitudeBox.realValue,
                            longitudeBox.realValue,
                            altitudeBox.value];
                case Command.SetSpeed:
                    return [commandBox.currentItem.type,
                            vehicle.fromSpeed(speedBox.value),
                            -1, 0];
                case Command.SetAltitude:
                    return [altitudeBox.value, 0];
                case Command.SetHome:
                    return [2, 0, 0, 0,
                            latitudeBox.realValue,
                            longitudeBox.realValue,
                            vehicle.barometric.fromDisplayedAltitude(altitudeBox.value)];
                default:
                    return [];
                }
            }
        }

        // TODO: commands arg edit widgets
        Controls.Label {
            text: qsTr("Alt.")
            font.pixelSize: sizings.fontPixelSize * 0.7
            font.bold: true
            visible: altitudeBox.visible
        }

        Controls.SpinBox {
            id: altitudeBox
            to: 20000 // TODO: borderValues
            visible: sendButton.command === Command.SetHome ||
                     sendButton.command === Command.SetAltitude ||
                     sendButton.command === Command.NavTo
            onVisibleChanged: if (visible) value = vehicle.barometric.displayedAltitude
            Layout.fillWidth: true
            Layout.columnSpan: 2
        }

        Controls.Label {
            text: qsTr("Lat.")
            font.pixelSize: sizings.fontPixelSize * 0.7
            font.bold: true
            visible: latitudeBox.visible
            Layout.fillWidth: true
        }

        Controls.CoordSpinBox {
            id: latitudeBox
            visible: sendButton.command === Command.SetHome || sendButton.command === Command.NavTo
            onVisibleChanged: if (visible) realValue = vehicle.position.latitude
            Layout.fillWidth: true
        }

        Controls.MapPickButton {
            id: pickButton
            visible: latitudeBox.visible
            Layout.rowSpan: 2
            onPicked: {
                latitudeBox.realValue = coordinate.latitude;
                longitudeBox.realValue = coordinate.longitude;

                map.pickerCoordinate = coordinate;
            }
            onVisibleChanged: {
                map.pickerVisible = visible;
                picking = false;
            }
        }

        Controls.Label {
            text: qsTr("Lon.")
            font.pixelSize: sizings.fontPixelSize * 0.7
            font.bold: true
            visible: latitudeBox.visible
            Layout.fillWidth: true
        }

        // FIXME: lat/lot edit widget
        Controls.CoordSpinBox {
            id: longitudeBox
            visible: latitudeBox.visible
            onVisibleChanged: if (visible) realValue = vehicle.position.longitude
            isLongitude: true
            Layout.fillWidth: true
        }

        Controls.Label {
            text: qsTr("Spd.")
            font.pixelSize: sizings.fontPixelSize * 0.7
            font.bold: true
            visible: speedBox.visible
        }

        Controls.SpinBox {
            id: speedBox
            visible: sendButton.command === Command.SetSpeed
            onVisibleChanged: if (visible) value = commandBox.currentItem.type ?
                                               vehicle.satellite.displayedGroundSpeed :
                                               vehicle.pitot.displayedIndicatedAirspeed
            to: 999 // TODO: borderValues
            Layout.fillWidth: true
            // TODO: suffix: speedUnits ? qsTr("km/h") : qsTr("m/s")
        }

        Controls.Label {
            text: qsTr("Cal.")
            font.pixelSize: sizings.fontPixelSize * 0.7
            font.bold: true
            visible: calibrationBox.visible
        }

        Controls.ComboBox {
            id: calibrationBox
            visible: sendButton.command === Command.PreflightCalibration
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
