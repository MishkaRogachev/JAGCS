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

    property int fix: -1
    property int eph: 0
    property int epv: 0
    property int satellitesVisible: 0

    ColumnLayout {
        id: column
        anchors.fill: parent
        spacing: sizings.spacing

        Instruments.SatelliteInstrument {
            visible: true // TODO: instruments settings
            Layout.fillWidth: true
        }
        /*Instruments.FlightInstrument {
            visible: true // TODO: instruments settings
            Layout.fillWidth: true
        }

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
