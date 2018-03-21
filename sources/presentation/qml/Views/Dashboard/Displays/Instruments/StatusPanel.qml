import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/JS/helper.js" as Helper
import "qrc:/Controls" as Controls
import "qrc:/Indicators" as Indicators

Controls.Pane {
    id: root

    property bool dmsFormat: settings.boolValue("Gui/coordinatesDms")

    RowLayout {
        anchors.centerIn: parent
        width: parent.width
        spacing: sizings.spacing

        Controls.ColoredIcon {
            id: snsIcon
            color: {
                switch (vehicle.satellite.fix) {
                case -1:
                case 0: return customPalette.sunkenColor;
                case 1: return customPalette.dangerColor;
                case 2: return customPalette.cautionColor;
                case 3:
                default: return customPalette.positiveColor;
                }
            }
            source: "qrc:/icons/gps.svg"
            height: sizings.controlBaseSize
            width: height
            Layout.alignment: Qt.AlignRight

            Text {
                text: vehicle.satellite.satellitesVisible
                font.pixelSize: parent.height / 4
                font.bold: true
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                color: parent.color
            }
        }

        ColumnLayout {
            id: column
            Layout.fillWidth: true
            spacing: sizings.spacing

            Controls.Label {
                font.pixelSize: Math.max(root.width * 0.04, sizings.fontPixelSize * 0.5)
                font.bold: true
                color: snsIcon.color
                text: qsTr("Lat.: ") + (dmsFormat ?
                           Helper.degreesToDmsString(vehicle.satellite.coordinate.latitude, false, 2) :
                           Helper.degreesToString(vehicle.satellite.coordinate.latitude, 6))
            }

            Controls.Label {
                font.pixelSize: Math.max(root.width * 0.04, sizings.fontPixelSize * 0.5)
                font.bold: true
                color: snsIcon.color
                text: qsTr("Lon.: ") + (dmsFormat ?
                           Helper.degreesToDmsString(vehicle.satellite.coordinate.longitude, true, 2) :
                           Helper.degreesToString(vehicle.satellite.coordinate.longitude, 6))
            }
        }

//        ColumnLayout { TODO: to satellites tooltip
//            Layout.alignment: Qt.AlignRight

//            Controls.Label {
//                font.pixelSize: Math.max(root.width * 0.04, sizings.fontPixelSize * 0.5)
//                font.bold: true
//                opacity: enabled ? 1 : 0.33
//                color: satelliteOperational ? customPalette.textColor : customPalette.dangerColor
//                text: qsTr("HDOP: ") + eph
//            }

//            Controls.Label {
//                font.pixelSize: Math.max(root.width * 0.04, sizings.fontPixelSize * 0.5)
//                font.bold: true
//                opacity: enabled ? 1 : 0.33
//                color: satelliteOperational ? customPalette.textColor : customPalette.dangerColor
//                text: qsTr("VDOP: ") + epv
//            }
//        }

        Item {
            Layout.fillWidth: true
        }

        Indicators.BatteryIndicator {
            id: battery
            percentage: vehicle.battery.percentage
        }

        ColumnLayout {
            Layout.alignment: Qt.AlignRight

            Controls.Label {
                font.pixelSize: sizings.fontPixelSize * 0.6
                font.bold: true
                color: vehicle.battery.voltage > 0.01 ? customPalette.textColor : customPalette.sunkenColor
                text: vehicle.battery.voltage.toFixed(2) + qsTr(" V")
            }

            Controls.Label {
                font.pixelSize: sizings.fontPixelSize * 0.6
                font.bold: true
                color: {
                    if (vehicle.battery.current < -0.01) return customPalette.positiveColor;
                    if (vehicle.battery.current > 0.0) return customPalette.textColor;
                    if (vehicle.battery.current > 5.0) return customPalette.cautionColor;
                    if (vehicle.battery.current > 10.0) return customPalette.dangerColor;

                    return customPalette.sunkenColor;
                }
                text: vehicle.battery.current.toFixed(2) + qsTr(" A")
            }
        }
    }
}
