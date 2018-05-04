import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls
import "../../DashboardControls" as DashboardControls

RowLayout {
    id: root

    Connections {
        target: display
        onUpdateCommandStatus: commandBox.updateCommandStatus(command, status)
    }

    spacing: sizings.spacing

    DashboardControls.Label {
        text: qsTr("Calibrate")
        horizontalAlignment: Text.AlignHCenter
        Layout.columnSpan: 3
        Layout.fillWidth: true
    }

    DashboardControls.CommandBox {
        id: commandBox
        tipText: qsTr("Select calibration")
        processingText: qsTr("Calibrating")
        model: [ { text: qsTr("Ref. pressure"), command: Command.CalibrateReferencePressure },
                 { text: qsTr("Airspeed"), command: Command.CalibrateAirspeed },
                 { text: qsTr("Temperature"), command: Command.CalibrateTemperature } ]
        Layout.fillWidth: true
    }
}
