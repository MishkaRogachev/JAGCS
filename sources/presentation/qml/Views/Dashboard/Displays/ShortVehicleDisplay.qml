import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/JS/helper.js" as Helper
import "qrc:/Controls" as Controls
import "qrc:/Indicators" as Indicators

import "CommandControls" as CommandControls

import "../Vehicles"

BaseVehicleDisplay { // FIXME: ShortAerialVehicleDisplay
    id: vehicleDisplay

    property AerialVehicle vehicle: AerialVehicle {}

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
        for (var i = 0; i < vehicle.mission.count; ++i) items.push(i + 1);
        itemBox.model = items;
    }

    Connections {
        target: vehicle.mission

        onCountChanged: updateItems()
        onCurrentChanged:itemBox.currentIndex = current
    }

    Component.onCompleted: updateItems()

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
                yaw: vehicle.ahrs.yaw
                Layout.rowSpan: 2

                Indicators.ArtificialHorizon {
                    id: ah
                    anchors.centerIn: parent
                    height: parent.height - parent.size * 2
                    width: height * 0.9
                    enabled: online &&  vehicle.ahrs.enabled
                    armed: vehicle.armed
                    pitch: vehicle.ahrs.pitch
                    roll: vehicle.ahrs.roll
                    rollInverted: settings.boolValue("Gui/fdRollInverted")

                    Indicators.BarIndicator {
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                        width: parent.width * 0.1
                        height: parent.height * 0.65
                        value: vehicle.powerSystem.throttle
                    }

                    Indicators.BarIndicator {
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.right: parent.right
                        width: parent.width * 0.1
                        height: parent.height * 0.7
                        value: vehicle.barometric.climb
                        fillColor: vehicle.barometric.climb > 0 ? palette.skyColor :
                                                                  palette.groundColor
                        minValue: -10
                        maxValue: 10 // TODO: to consts
                    }
                }
            }

            ColumnLayout {
                spacing: sizings.spacing

                Indicators.FdLabel {
                    digits: 0
                    value: vehicle.satellite.displayedGroundSpeed
                    enabled: vehicle.satellite.enabled
                    operational: vehicle.satellite.operational
                    prefix: qsTr("GS") + ", " + vehicle.speedSuffix
                    Layout.alignment: Qt.AlignHCenter
                }

                Indicators.FdLabel {
                    value: vehicle.barometric.displayedAltitude
                    enabled: vehicle.barometric.enabled
                    operational: vehicle.barometric.operational
                    prefix: qsTr("ALT") + ", " + vehicle.altitudeSuffix
                    Layout.alignment: Qt.AlignHCenter
                }
            }

            ColumnLayout {
                spacing: sizings.spacing

                RowLayout {
                    spacing: sizings.spacing

                    Controls.ColoredIcon {
                        id: icon
                        source: translator.imageFromVehicleState(vehicle.vehicleState)
                        height: sizings.controlBaseSize * 0.75
                        width: height
                        color: {
                            switch (vehicle.vehicleState) {
                            case Domain.Active: return palette.missionColor;
                            case Domain.Boot:
                            case Domain.Calibrating: return palette.selectionColor;
                            case Domain.Critical: return palette.dangerColor;
                            case Domain.Emergency: return palette.cautionColor;
                            case Domain.Standby: return palette.positiveColor;
                            case Domain.UnknownState:
                            default: return palette.sunkenColor;
                            }
                        }
                        Behavior on color { ColorAnimation { duration: 200 } }
                    }

                    Controls.Label {
                        text: vehicleName
                        font.pixelSize: sizings.fontPixelSize * 0.75
                        font.bold: true
                        height: sizings.controlBaseSize * 0.75
                        wrapMode: Text.NoWrap
                        Layout.fillWidth: true
                    }
                }

                CommandControls.ModeBox {
                    id: modeBox
                    mode: vehicle.mode
                    model: vehicle.availableModes
                    enabled: online
                    implicitHeight: sizings.controlBaseSize * 0.75
                    Layout.fillWidth: true
                }

                CommandControls.WaypointBox {
                    id: itemBox
                    enabled: online && vehicle.mission.count > 0
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
                    onClicked: dashboard.selectVehicle(vehicleId)
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
