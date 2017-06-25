import QtQuick 2.6
import QtQuick.Layouts 1.3

import "../Controls" as Controls

Item {
    id: root

    property real batteryVoltage: 0
    property real batteryCurrent: 0
    property alias batteryPercentage: battery.percentage

    implicitHeight: row.height

    RowLayout {
        id: row
        anchors.centerIn: parent
        width: parent.width

        BatteryIndicator {
            id: battery
            Layout.alignment: Qt.AlignRight
        }

        Controls.Label {
            font.pixelSize: root.width * 0.044
            font.bold: true
            color: battery.color
            text: batteryVoltage.toFixed(2) + qsTr(" V")
        }

        Controls.ColoredIcon {
            id: current
            source: "qrc:/icons/current.svg"
            implicitWidth: palette.controlBaseSize
            implicitHeight: width
            color: {
                if (batteryCurrent < -0.01)
                    return palette.positiveColor;
                if (batteryCurrent > 0.01)
                    return palette.neutralColor;

                return palette.textColor;
            }
            Layout.alignment: Qt.AlignRight
        }

        Controls.Label {
            font.pixelSize: root.width * 0.044
            font.bold: true
            color: current.color
            text: batteryCurrent.toFixed(2) + qsTr(" A")
        }
    }
}
