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

    property bool ahrsOperational: false
    property real yawspeed: 0.0

    property real course: 0
    property int fix: -1
    property int eph: 0
    property int epv: 0
    property int satelliteAltitude: 0
    property int satellitesVisible: 0

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

    ColumnLayout {
        id: column
        width: parent.width
        spacing: sizings.spacing

        Instruments.SatelliteInstrument {
            visible: true // TODO: instruments settings
            Layout.fillWidth: true
        }

        Instruments.FlightInstrument {
            visible: true // TODO: instruments settings
            Layout.fillWidth: true
        }

        Instruments.NavigationInstrument  {
            visible: true // TODO: instruments settings
            Layout.fillWidth: true
        }

        Instruments.ControlInstrument  {
            id: control
            visible: true // TODO: instruments settings
            Layout.fillWidth: true

            Connections {
                target: vehicleDisplay
                onUpdateCommandStatus: control.updateCommandStatus(command, status)
            }
        }

        Instruments.MissionInstrument  {
            id: mission
            visible: true // TODO: instruments settings
            Layout.fillWidth: true

            Connections {
                target: vehicleDisplay
                onCurrentItemChanged: mission.current = currentItem
                onUpdateCommandStatus: mission.updateCommandStatus(command, status)
            }
        }
    }
}
