import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls
import "qrc:/Indicators" as Indicators

GridLayout {
    id: root

    property bool armed: false
    property string mode: qsTr("None")
    property real batteryVoltage: 0
    property real batteryCurrent: 0
    property alias batteryPercentage: battery.percentage

    signal commandStatusChanged(var command, var status)
    signal executeCommand(int command)
    signal executeBoolCommand(int command, bool check)
    signal rejectCommand(int command)

    columns: 4

    Indicators.BatteryIndicator {
        id: battery
        Layout.alignment: Qt.AlignRight
    }

    Controls.Label {
        font.pixelSize: palette.fontPixelSize * 0.75
        font.bold: true
        color: battery.color
        text: batteryVoltage.toFixed(2) + qsTr(" V")
    }

    Controls.ColoredIcon { // TODO: wind avability
        id: current
        source: "qrc:/icons/current.svg"
        implicitWidth: palette.controlBaseSize
        implicitHeight: width
        color: {
            if (batteryCurrent < -0.01)
                return palette.positiveColor;
            if (batteryCurrent > 0.0)
                return palette.textColor;
            if (batteryCurrent > 5.0)
                return palette.neutralColor;
            if (batteryCurrent > 10.0)
                return palette.negativeColor; // TODO: settings

            return palette.disabledColor;
        }
        Layout.alignment: Qt.AlignRight
    }

    Controls.Label {
        font.pixelSize: palette.fontPixelSize * 0.75
        font.bold: true
        color: current.color
        text: batteryCurrent.toFixed(2) + qsTr(" A")
    }

    Controls.CommandSwitch { // FIXME: dangerous button
        command: Command.ArmDisarm
        text: armed ? qsTr("DISARM") : qsTr("ARM")
        inputChecked: armed
        Layout.columnSpan: 2
    }

    Controls.Label {
        font.pixelSize: palette.fontPixelSize * 0.75
        font.bold: true
        text: mode
        horizontalAlignment: Qt.AlignHCenter
        Layout.fillWidth: true
        Layout.columnSpan: 2
    }
}
