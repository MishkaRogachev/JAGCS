import QtQuick 2.6
import QtQuick.Layouts 1.3

import "qrc:/Controls" as Controls
import "qrc:/Indicators" as Indicators

Controls.Pane {
    id: root

    GridLayout {
        anchors.centerIn: parent
        width: parent.width
        rowSpacing: sizings.spacing
        columnSpacing: sizings.spacing
        columns: 3

        Controls.Label {
            text: vehicleName
            font.pixelSize: sizings.fontPixelSize * 0.75
            font.bold: true
            Layout.fillWidth: true
        }

        Indicators.BatteryIndicator {
            id: battery
            percentage: batteryPercentage
            Layout.rowSpan: 2
        }

        Controls.Label {
            font.pixelSize: sizings.fontPixelSize * 0.6
            font.bold: true
            color: batteryVoltage > 0.01 ? palette.textColor : palette.sunkenColor
            text: batteryVoltage.toFixed(2) + qsTr(" V")
        }

        Controls.Label {
            text: translator.translateVehicleState(vehicleState)
            font.pixelSize: sizings.fontPixelSize * 0.75
            font.bold: true
            Layout.fillWidth: true
        }

        Controls.Label {
            font.pixelSize: sizings.fontPixelSize * 0.6
            font.bold: true
            color: {
                if (batteryCurrent < -0.01) return palette.positiveColor;
                if (batteryCurrent > 0.0) return palette.textColor;
                if (batteryCurrent > 5.0) return palette.cautionColor;
                if (batteryCurrent > 10.0) return palette.dangerColor;

                return palette.sunkenColor;
            }
            text: batteryCurrent.toFixed(2) + qsTr(" A")
        }
    }
}
