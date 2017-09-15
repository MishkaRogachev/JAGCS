import QtQuick 2.6
import QtQuick.Layouts 1.3
import QtPositioning 5.6

import "qrc:/JS/helper.js" as Helper
import "qrc:/Controls" as Controls

BaseDisplay {
    id: root

    property bool satelliteEnabled: false
    property bool satelliteOperational: false
    property int fix: -1
    property int eph: 0
    property int epv: 0
    property int satellitesVisible: 0
    property var coordinate: QtPositioning.coordinate()

    property bool dmsFormat: settings.boolValue("Gui/coordinatesDms")

    implicitHeight: row.height

    RowLayout {
        id: row
        anchors.centerIn: parent
        width: parent.width

        ColumnLayout {
            id: column
            Layout.fillWidth: true

            Controls.Label {
                font.pixelSize: root.width * 0.044
                font.bold: true
                opacity: enabled ? 1 : 0.33
                color: satelliteOperational ? palette.textColor : palette.dangerColor
                text: qsTr("Lat.: ") + (dmsFormat ?
                                            Helper.degreesToDmsString(coordinate.latitude, false) :
                                            Helper.degreesToString(coordinate.latitude, 6))
            }

            Controls.Label {
                font.pixelSize: root.width * 0.044
                font.bold: true
                opacity: enabled ? 1 : 0.33
                color: satelliteOperational ? palette.textColor : palette.dangerColor
                text: qsTr("Lon.: ") + (dmsFormat ?
                                            Helper.degreesToDmsString(coordinate.longitude, true) :
                                            Helper.degreesToString(coordinate.longitude, 6))
            }
        }

        Item {
            Layout.fillWidth: true
        }

        Controls.ColoredIcon {
            opacity: enabled ? 1 : 0.33
            color: {
                switch (fix) {
                case -1:
                case 0: return palette.sunkenColor;
                case 1: return palette.dangerColor;
                case 2: return palette.cautionColor;
                case 3:
                default: return palette.positiveColor;
                }
            }
            source: "qrc:/icons/gps.svg"
            height: palette.controlBaseSize
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
                font.pixelSize: root.width * 0.044
                font.bold: true
                opacity: enabled ? 1 : 0.33
                color: satelliteOperational ? palette.textColor : palette.dangerColor
                text: qsTr("HDOP: ") + eph
            }

            Controls.Label {
                font.pixelSize: root.width * 0.044
                font.bold: true
                opacity: enabled ? 1 : 0.33
                color: satelliteOperational ? palette.textColor : palette.dangerColor
                text: qsTr("VDOP: ") + epv
            }
        }
    }
}
