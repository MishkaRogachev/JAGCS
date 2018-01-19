import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/JS/helper.js" as Helper
import "qrc:/Controls" as Controls
import "qrc:/Indicators" as Indicators

import "CommandControls" as CommandControls
import "Instruments" as Instruments

BaseVehicleDisplay {
    id: vehicleDisplay

    property bool batteryEnabled: false
    property bool batteryOperational: false
    property real batteryVoltage: 0
    property real batteryCurrent: 0
    property int batteryPercentage: 0

    property bool ahrsOperational: false
    property real yawspeed: 0.0
    property vector3d vibration

    property real velocityVariance: 0.0
    property real verticalVariance: 0.0
    property real horizontVariance: 0.0
    property real compassVariance: 0.0
    property real terrainAltitudeVariance: 0.0

    property real course: 0
    property int fix: -1
    property int eph: 0
    property int epv: 0
    property int satelliteAltitude: 0
    property int satellitesVisible: 0

    property bool pitotPresent: false
    property bool pitotEnabled: false
    property bool pitotOperational: false
    property real indicatedAirspeed: 0.0
    property real trueAirspeed: 0.0
    property real displayedIndicatedAirspeed: {
        switch (speedUnits) {
        default:
        case 0: return indicatedAirspeed;
        case 1: return Helper.mpsToKph(indicatedAirspeed);
        }
    }
    property real displayedTrueAirspeed: {
        switch (speedUnits) {
        default:
        case 0: return trueAirspeed;
        case 1: return Helper.mpsToKph(trueAirspeed);
        }
    }

    property real desiredPitch: 0.0
    property real desiredRoll: 0.0
    property real targetBearing: 0.0
    property real desiredHeading: 0.0
    property real trackError: 0.0
    property real airspeedError: 0.0
    property real altitudeError: 0.0
    property int targetDistance: 0
    property real displayedAirspeedError: {
        switch (speedUnits) {
        default:
        case 0: return airspeedError;
        case 1: return Helper.mpsToKph(airspeedError);
        }
    }

    property bool rangefinderEnabled: false
    property bool rangefinderOperational: false
    property real rangefinderHeight: 0

    property bool compassEnabled: false
    property bool compassOperational: false
    property real heading: 0.0

    property real windDirection: 0
    property real windSpeed: 0
    property real displayedWindSpeed: {
        switch (speedUnits) {
        default:
        case 0: return windSpeed;
        case 1: return Helper.mpsToKph(windSpeed);
        }
    }

    implicitWidth: column.implicitWidth
    implicitHeight: column.implicitHeight

    Connections {
        target: displaysSettingsButton
        onClicked: instrumentsVisibility.visible ? instrumentsVisibility.close() :
                                                   instrumentsVisibility.open()
    }

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
                    { text: qsTr("Diagnostics panel"), instrument: diagnostics },
                    { text: qsTr("Status panel"), instrument: status },
                    { text: qsTr("Flight instrument(FD)"), instrument: fd },
                    { text: qsTr("Horizontal situation indicator(HSI)"), instrument: hsi },
                    { text: qsTr("Mission control"), instrument: mission },
                    { text: qsTr("Control panel"), instrument: control }
                ]

                Controls.CheckBox {
                    text: modelData.text
                    checked: modelData.instrument.visible
                    onCheckedChanged: modelData.instrument.visible = checked
                }
            }
        }
    }

    ColumnLayout {
        id: column
        width: parent.width
        spacing: sizings.spacing
        // TODO: initial visibility to settings

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

            Connections {
                target: vehicleDisplay
                onCurrentItemChanged: mission.current = currentItem
                onUpdateCommandStatus: mission.updateCommandStatus(command, status)
            }
        }

        Instruments.ControlPanel {
            id: control
            Layout.fillWidth: true

            Connections {
                target: vehicleDisplay
                onUpdateCommandStatus: control.updateCommandStatus(command, status)
            }
        }
    }
}
