import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/JS/helper.js" as Helper
import "qrc:/Controls" as Controls
import "qrc:/Indicators" as Indicators
import "../CommandControls" as CommandControls

Controls.Pane { // TODO: base vehicle display
    id: vehicleDisplay

    property int vehicleId: 0
    property string vehicleName

    property bool online: false
    property alias armed: ah.armed

    property int mode: Domain.None
    property var availableModes: []

    property alias ahrsEnabled: ah.enabled
    property alias ahrsOperational: ah.operational
    property alias pitch: ah.pitch
    property alias roll: ah.roll
    property alias yaw: compass.yaw

    property int throttle: 0

    property bool satelliteEnabled: false
    property bool satelliteOperational: false
    property real groundspeed: 0

    property bool barometricEnabled: false
    property bool barometricOperational: false
    property int barometricAltitude: 0
    property real barometricClimb: 0

    property int homeAltitude: 0

    property bool rollInverted: settings.boolValue("Gui/fdRollInverted")
    property int speedUnits: settings.value("Gui/fdSpeedUnits")
    property bool altitudeRelative: settings.boolValue("Gui/fdRelativeAltitude")

    function updateCommandStatus(command, status) {
        switch (command) {
        case Command.SetMode:
            modeBox.status = status;
            break;
        case Command.Return:
            rtl.status = status;
            break;
        default:
            break;
        }
    }

    VehicleDisplayPresenter {
        id: presenter
        view: vehicleDisplay
        Component.onCompleted: setVehicle(vehicleId)
    }

    RowLayout {
        anchors.fill: parent

        Indicators.YawIndicator {
            id: compass
            implicitWidth: height
            Layout.rowSpan: 2
            Layout.fillHeight: true

            Indicators.ArtificialHorizon {
                id: ah
                available: online
                anchors.centerIn: parent
                height: parent.height - parent.size * 2
                width: height * 0.9
                rollInverted:  settings.boolValue("Gui/fdRollInverted")

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
            Indicators.FdLabel {
                digits: 0
                value: {
                    switch (speedUnits) {
                    default:
                    case 0: return groundspeed;
                    case 1: return Helper.mpsToKph(groundspeed);
                    }
                }
                enabled: satelliteEnabled
                operational: satelliteOperational
                prefix: qsTr("GS")
                suffix: speedUnits ? qsTr("km/h") : qsTr("m/s")
                Layout.minimumWidth: sizings.controlBaseSize * 1.5
            }

            Indicators.FdLabel {
                value: altitudeRelative ? barometricAltitude - homeAltitude : barometricAltitude
                enabled: barometricEnabled
                operational: barometricOperational
                prefix: qsTr("ALT")
                suffix: qsTr("m")
                Layout.minimumWidth: sizings.controlBaseSize * 1.5
            }
        }

        GridLayout {
            Layout.fillWidth: true
            columns: 2

            Controls.Label {
                text: vehicleName
                font.pixelSize: sizings.fontPixelSize * 0.75
                font.bold: true
                Layout.fillWidth: true
            }

            Controls.Button {
                flat: true
                iconSource: "qrc:/icons/right.svg"
                onClicked: dashboard.selectVehicle(vehicleId, vehicleName)
            }

            CommandControls.ModeBox {
                id: modeBox
                mode: vehicleDisplay.mode
                model: availableModes
                font.pixelSize: sizings.fontPixelSize * 0.75
                enabled: online
                tipText: qsTr("Select mode")
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
        // TODO: select mission item
    }
}
