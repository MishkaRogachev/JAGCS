import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/JS/helper.js" as Helper
import "qrc:/Controls" as Controls
import "qrc:/Indicators" as Indicators

import "CommandControls" as CommandControls

BaseVehicleDisplay {
    id: vehicleDisplay

    property real yaw: 0.0

    onUpdateCommandStatus:  {
        switch (command) {
        case Command.SetMode:
            modeBox.status = status;
            break;
        case Command.Return:
            rtl.status = status;
            break;
        case Command.GoTo:
            itemBox.status = status;
            break;
        default:
            break;
        }
    }

    function updateItems() {
        var items = [];
        for (var i = 0; i < missionItems; ++i) items.push(i + 1);
        itemBox.model = items;
    }

    Component.onCompleted: updateItems()
    onMissionItemsChanged: updateItems()
    onCurrentItemChanged: itemBox.currentIndex = currentItem

    implicitWidth: pane.implicitWidth
    implicitHeight: pane.implicitHeight

    Controls.Pane {
        id: pane
        anchors.fill: parent

        RowLayout {
            anchors.fill: parent
            spacing: sizings.spacing

            Indicators.YawIndicator {
                id: compass
                implicitWidth: sizings.controlBaseSize * 2
                implicitHeight: width
                yaw: vehicleDisplay.yaw
                Layout.rowSpan: 2

                Indicators.ArtificialHorizon {
                    id: ah
                    anchors.centerIn: parent
                    height: parent.height - parent.size * 2
                    width: height * 0.9
                    enabled: online && ahrsEnabled
                    armed: vehicleDisplay.armed
                    pitch: vehicleDisplay.pitch
                    roll: vehicleDisplay.roll
                    rollInverted: settings.boolValue("Gui/fdRollInverted")

                    Indicators.BarIndicator {
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                        width: parent.width * 0.1
                        height: parent.height * 0.65
                        value: throttle
                    }

                    Indicators.BarIndicator {
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.right: parent.right
                        width: parent.width * 0.1
                        height: parent.height * 0.7
                        value: barometricClimb
                        fillColor: barometricClimb > 0 ? palette.skyColor : palette.groundColor
                        minValue: -10
                        maxValue: 10 // TODO: to consts
                    }
                }
            }

            ColumnLayout {
                spacing: sizings.spacing

                Indicators.FdLabel {
                    digits: 0
                    value: displayedGroundSpeed
                    enabled: satelliteEnabled
                    operational: satelliteOperational
                    prefix: qsTr("GS") + ", " + speedSuffix
                    Layout.alignment: Qt.AlignHCenter
                }

                Indicators.FdLabel {
                    value: displayedAltitude
                    enabled: barometricEnabled
                    operational: barometricOperational
                    prefix: qsTr("ALT") + ", " + altitudeSuffix
                    Layout.alignment: Qt.AlignHCenter
                }
            }

            ColumnLayout {
                spacing: sizings.spacing

                Controls.Label {
                    text: vehicleName
                    font.pixelSize: sizings.fontPixelSize * 0.75
                    font.bold: true
                    height: sizings.controlBaseSize * 0.75
                    wrapMode: Text.NoWrap
                    Layout.fillWidth: true
                }

                CommandControls.ModeBox {
                    id: modeBox
                    mode: vehicleDisplay.mode
                    model: availableModes
                    enabled: online
                    implicitHeight: sizings.controlBaseSize * 0.75
                    Layout.fillWidth: true
                }

                CommandControls.WaypointBox {
                    id: itemBox
                    enabled: online && missionItems > 0
                    implicitHeight: sizings.controlBaseSize * 0.75
                    Layout.fillWidth: true
                }
            }

            ColumnLayout {
                spacing: sizings.spacing
                Layout.alignment: Qt.AlignVCenter | Qt.AlignRight

                Controls.Button {
                    flat: true
                    iconSource: "qrc:/icons/right.svg"
                    onClicked: dashboard.selectVehicle(vehicleId, vehicleName)
                }

                CommandControls.Button {
                    id: rtl
                    tipText: qsTr("Return to launch")
                    iconSource: "qrc:/icons/home.svg"
                    enabled: online
                    command: Command.Return
                }
            }
        }
    }
}
