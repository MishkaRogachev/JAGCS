import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls
import "../CommandControls" as CommandControls

Controls.Pane {
    id: root

    property int count: vehicle.mission.count
    property int current: vehicle.mission.current

    Component.onCompleted: updateItems()
    onCurrentChanged: updateCurrent()
    onCountChanged: updateItems()

    function updateItems() {
        var items = [];
        for (var i = 0; i < count; ++i) items.push(i + 1);
        itemBox.model = items;
    }

    function updateCurrent() {
        itemBox.currentIndex = vehicle.mission.current;
    }

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
            case Command.GoTo:
                itemBox.status = status;
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

    ColumnLayout {
        anchors.fill: parent
        spacing: sizings.spacing

        RowLayout {
             spacing: sizings.spacing

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
        }

        RowLayout {
            enabled: count > 0
            spacing: sizings.spacing
            visible: vehicle.mode === Domain.Mission

            Controls.Label {
                text: qsTr("WP")
                font.pixelSize: sizings.fontPixelSize * 0.7
                font.bold: true
                Layout.fillWidth: true
            }

            Controls.Button {
                tipText: qsTr("Goto left")
                iconSource: "qrc:/icons/left.svg"
                enabled: current > 1
                onClicked: itemBox.goTo(current - 1)
            }

            CommandControls.WaypointBox {
                id: itemBox
                Layout.preferredWidth: sizings.controlBaseSize * 3
            }

            Controls.Button {
                tipText: qsTr("Goto right")
                iconSource: "qrc:/icons/right.svg"
                enabled: current < count - 1
                onClicked: itemBox.goTo(current + 1)
            }
        }

        GridLayout { // TODO: NavTo Item
            rowSpacing: sizings.spacing
            columnSpacing: sizings.spacing
            columns: 4
            visible: vehicle.mode === Domain.NavTo
            onVisibleChanged: updateLatLonAlt()
            Component.onCompleted: updateLatLonAlt()

            function updateLatLonAlt() {
                altitudeBox.value = vehicle.barometric.displayedAltitude;
                latitudeBox.value = vehicle.position.latitude;
                longitudeBox.value =vehicle.position.longitude;
            }

            Controls.Label {
                text: qsTr("Alt.")
                font.pixelSize: sizings.fontPixelSize * 0.7
                font.bold: true
            }

            Controls.SpinBox {
                id: altitudeBox
                to: 20000 // TODO: borderValues
                Layout.fillWidth: true
            }

            Controls.MapPickButton {
                id: pickButton
                onPicked: {
                    latitudeBox.value = coordinate.latitude;
                    longitudeBox.value = coordinate.longitude;
                    map.pickerCoordinate = coordinate;
                }
                onVisibleChanged: {
                    map.pickerVisible = visible;
                    picking = false;
                }
            }

            CommandControls.Button {
                id: sendButton
                command: Command.NavTo
                iconSource: "qrc:/icons/play.svg"
                tipText: qsTr("Send point")
                args: [ latitudeBox.value, longitudeBox.value,
                    vehicle.barometric.fromDisplayedAltitude(altitudeBox.value) ]
            }

            Controls.Label {
                text: qsTr("Lat.")
                font.pixelSize: sizings.fontPixelSize * 0.7
                font.bold: true
            }

            Controls.CoordSpinBox {
                id: latitudeBox
                Layout.fillWidth: true
                Layout.columnSpan: 3
            }

            Controls.Label {
                text: qsTr("Lon.")
                font.pixelSize: sizings.fontPixelSize * 0.7
                font.bold: true
            }

            Controls.CoordSpinBox {
                id: longitudeBox
                isLongitude: true
                Layout.fillWidth: true
                Layout.columnSpan: 3
            }
        }
    }
}
