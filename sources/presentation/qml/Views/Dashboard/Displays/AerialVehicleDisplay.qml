import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/JS/helper.js" as Helper
import "qrc:/Controls" as Controls
import "qrc:/Indicators" as Indicators

import "CommandControls" as CommandControls
import "Instruments" as Instruments

import "../Vehicles"

Item {
    id: vehicleDisplay

    property int vehicleId: 0

    property AerialVehicle vehicle: AerialVehicle {}

    function updateCommandStatus(command, status) {
        mission.updateCommandStatus(command, status);
        control.updateCommandStatus(command, status);
    }

    implicitWidth: column.implicitWidth
    implicitHeight: column.implicitHeight + sizings.shadowSize

    VehicleDisplayPresenter {
        id: presenter
        view: vehicleDisplay
        Component.onCompleted: setVehicle(vehicleId)
    }

    Connections {
        target: displaysSettingsButton
        onClicked: instrumentsVisibility.visible ? instrumentsVisibility.close() :
                                                   instrumentsVisibility.open()
    }

//    TODO: instruments to ListModel {
//        id: instrumentsModel
//    }

    Controls.Popup {
        id: instrumentsVisibility
        x: displaysSettingsButton.x
        y: -sizings.padding
        closePolicy: Controls.Popup.NoAutoClose
        padding: sizings.padding

        ColumnLayout {
            spacing: sizings.spacing

            Repeater {
                model: [
                    { text: qsTr("Diagnostics panel"), instrument: diagnostics,
                        setting: "diagnosticsVisible" },
                    { text: qsTr("Status panel"), instrument: status,
                        setting: "statusVisible" },
                    { text: qsTr("Flight instrument(FD)"), instrument: fd,
                        setting: "fdVisible" },
                    { text: qsTr("Horizontal situation indicator(HSI)"), instrument: hsi,
                        setting: "hsiVisible" },
                    { text: qsTr("Mission control"), instrument: mission,
                        setting: "missionVisible" },
                    { text: qsTr("Control panel"), instrument: control,
                        setting: "controlVisible" }
                ]

                Controls.CheckBox {
                    text: modelData.text
                    checked: modelData.instrument.visible
                    onCheckedChanged: modelData.instrument.visible = checked
                    onClicked: settings.setValue("veh_" + vehicleId + "/" +
                                                  modelData.setting, checked)
                    Component.onCompleted: {
                        checked = settings.boolValue("veh_" + vehicleId + "/" +
                                                     modelData.setting, true);
                        modelData.instrument.visible = checked;
                    }
                }
            }
        }
    }

    Flickable { // ListView { spacing: sizings.spacing
        id: list
        width: vehicleDisplay.width - sizings.shadowSize
        height: vehicleDisplay.height - sizings.shadowSize
        flickableDirection: Flickable.AutoFlickIfNeeded
        boundsBehavior: Flickable.StopAtBounds
        contentHeight: column.height

        Controls.ScrollBar.vertical: Controls.ScrollBar {
            visible: parent.contentHeight > parent.height
        }

        ColumnLayout {
            id: column
            width: parent.width
            spacing: sizings.spacing

            Instruments.DiagnosticsPanel {
                id: diagnostics
                Layout.fillWidth: true
            }

            Instruments.StatusPanel {
                id: status
                Layout.fillWidth: true
            }

            Instruments.FlightDirector {
                id: fd
                Layout.fillWidth: true
            }

            Instruments.HorizontalSituationIndicator  {
                id: hsi
                Layout.fillWidth: true
            }

            Instruments.MissionControl  {
                id: mission
                Layout.fillWidth: true
            }

            Instruments.ControlPanel {
                id: control
                Layout.fillWidth: true
            }
        }
    }
}
