import QtQuick 2.6
import QtQuick.Layouts 1.3

import "qrc:/Controls" as Controls
import "qrc:/Indicators" as Indicators

Controls.Pane {
    id: root

    property real batteryVoltage: 0
    property real batteryCurrent: 0
    property int batteryPercentage: 0

    implicitHeight: row.height

    RowLayout {
        id: row
        anchors.centerIn: parent
        width: parent.width
        spacing: sizings.spacing

        Indicators.BatteryIndicator {
            id: battery
            percentage: batteryPercentage
        }

        Controls.Label {
            font.pixelSize: sizings.fontPixelSize * 0.6
            font.bold: true
            color: batteryVoltage > 0.01 ? palette.textColor : palette.sunkenColor
            text: batteryVoltage.toFixed(2) + qsTr(" V")
        }

        Controls.ColoredIcon {
            id: current
            source: "qrc:/icons/current.svg"
            color: {
                if (batteryCurrent < -0.01)
                    return palette.positiveColor;
                if (batteryCurrent > 0.0)
                    return palette.textColor;
                if (batteryCurrent > 5.0)
                    return palette.cautionColor;
                if (batteryCurrent > 10.0)
                    return palette.dangerColor;

                return palette.sunkenColor;
            }
        }

        Controls.Label {
            font.pixelSize: sizings.fontPixelSize * 0.6
            font.bold: true
            color: current.color
            text: batteryCurrent.toFixed(2) + qsTr(" A")
        }
    }
}
