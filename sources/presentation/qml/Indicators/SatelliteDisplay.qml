import QtQuick 2.6
import QtQuick.Layouts 1.3
import QtPositioning 5.6

import "qrc:/JS/helper.js" as Helper
import "../Controls" as Controls

Item {
    id: root

    property bool satelliteOperational: false
    property int fix: -1
    property int eph: 0
    property int epv: 0
    property int satellitesVisible: 0
    property var coordinate: QtPositioning.coordinate()

    implicitHeight: row.height

    RowLayout {
        id: row
        anchors.centerIn: parent
        width: parent.width

        ColumnLayout {
            id: column
            Layout.fillWidth: true

            Controls.Label {
                font.pixelSize: root.width * 0.042
                font.bold: true
                color: satelliteOperational ? palette.textColor : palette.disabledColor
                text: qsTr("Lat.: ") + Helper.degreesToDmsString(coordinate.latitude, false)
            }

            Controls.Label {
                font.pixelSize: root.width * 0.042
                font.bold: true
                color: satelliteOperational ? palette.textColor : palette.disabledColor
                text: qsTr("Lon.: ") + Helper.degreesToDmsString(coordinate.longitude, true)
            }
        }

        Item {
            Layout.fillWidth: true
        }

        Controls.ColoredIcon {
            color: {
                switch (fix) {
                case -1:
                case 0: return palette.disabledColor;
                case 1: return palette.negativeColor;
                case 2: return palette.neutralColor;
                case 3:
                default: return palette.positiveColor;
                }
            }
            source: "qrc:/icons/gps.svg"
            height: column.height
            width: height
            Layout.alignment: Qt.AlignRight

            Text {
                text: satellitesVisible
                font.pixelSize: parent.height / 4
                font.bold: true
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                color: parent.color
            }
        }

        ColumnLayout {
            Layout.alignment: Qt.AlignRight

            Controls.Label {
                font.pixelSize: root.width * 0.042
                font.bold: true
                color: satelliteOperational ? palette.textColor : palette.disabledColor
                text: qsTr("HDOP: ") + eph
            }

            Controls.Label {
                font.pixelSize: root.width * 0.042
                font.bold: true
                color: satelliteOperational ? palette.textColor : palette.disabledColor
                text: qsTr("VDOP: ") + epv
            }
        }
    }
}
