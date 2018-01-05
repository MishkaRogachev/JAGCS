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

    property real desiredPitch: 0.0
    property real desiredRoll: 0.0

    property int fix: -1
    property int eph: 0
    property int epv: 0
    property int satelliteAltitude: 0
    property int satellitesVisible: 0

    property bool pitotEnabled: false
    property bool pitotOperational: false
    property real indicatedAirspeed: 0
    property real trueAirspeed: 0
    property real airspeedError: 0

    property real altitudeError: 0

    property bool rangefinderEnabled: false
    property bool rangefinderOperational: false
    property real rangefinderHeight: 0

    ColumnLayout {
        id: column
        anchors.fill: parent
        spacing: sizings.spacing

        Instruments.SatelliteInstrument {
            visible: true // TODO: instruments settings
            Layout.fillWidth: true
        }

        Instruments.FlightInstrument {
            visible: true // TODO: instruments settings
            Layout.fillWidth: true
        }
/*
        Instruments.NavigationInstrument  {
            visible: true // TODO: instruments settings
            Layout.fillWidth: true
        }

        Instruments.ControlInstrument  {
            visible: true // TODO: instruments settings
            Layout.fillWidth: true
        }

        Instruments.MissionInstrument  {
            visible: true // TODO: instruments settings
            Layout.fillWidth: true
        }*/
    }
}
