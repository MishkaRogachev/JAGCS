import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls
import "qrc:/Indicators" as Indicators

RowLayout {
    id: root

    property string mode: qsTr("None")
    property real batteryVoltage: 0
    property real batteryCurrent: 0
    property alias batteryPercentage: battery.percentage

    Controls.Label {
        font.pixelSize: palette.fontPixelSize * 0.75
        font.bold: true
        text: mode
        horizontalAlignment: Qt.AlignHCenter
        Layout.fillWidth: true
    }

    Indicators.BatteryIndicator {
        id: battery
        Layout.alignment: Qt.AlignRight
    }

    ColumnLayout {
        Layout.alignment: Qt.AlignRight

        Controls.Label {
            font.pixelSize: palette.fontPixelSize * 0.6
            font.bold: true
            color: battery.color
            text: batteryVoltage.toFixed(2) + qsTr(" V")
        }

        Controls.Label {
            font.pixelSize: palette.fontPixelSize * 0.6
            font.bold: true
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
            text: batteryCurrent.toFixed(2) + qsTr(" A")
        }
    }
}
