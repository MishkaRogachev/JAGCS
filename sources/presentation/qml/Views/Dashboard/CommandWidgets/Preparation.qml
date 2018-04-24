import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls
import "../DashboardControls" as DashboardControls

GridLayout {
    id: root

    Connections {
        target: vehicleDisplay
        onUpdateCommandStatus: {
            switch (command) {
            case Command.CalibrateReferencePressure:
                pressureButton.status = status;
                break;
            case Command.CalibrateAirspeed:
                airspeedButton.status = status;
                break;
            case Command.CalibrateTemperature:
                temperatureButton.status = status;
                break;
            default:
                break;
            }
        }
    }

    columns: 3
    rowSpacing: sizings.spacing
    columnSpacing: sizings.spacing

    DashboardControls.Label {
        text: qsTr("Calibrate")
        horizontalAlignment: Text.AlignHCenter
        Layout.columnSpan: 3
        Layout.fillWidth: true
    }

    DashboardControls.CommandButton {
        id: pressureButton
        command: Command.CalibrateReferencePressure
        //iconSource: "qrc:/icons/pressure.svg"
        text: qsTr("Ref. pressure")
        Layout.fillWidth: true
    }

    DashboardControls.CommandButton {
        id: airspeedButton
        command: Command.CalibrateAirspeed
        //iconSource: "qrc:/icons/speed.svg"
        text: qsTr("Airspd.")
        Layout.fillWidth: true
    }

    DashboardControls.CommandButton {
        id: temperatureButton
        command: Command.CalibrateTemperature
        //iconSource: "qrc:/icons/temperature.svg"
        text: qsTr("Temp.")
        Layout.fillWidth: true
    }
}
