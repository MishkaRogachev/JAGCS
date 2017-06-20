import QtQuick 2.6
import QtQuick.Layouts 1.3
import QtPositioning 5.6

import "qrc:/JS/helper.js" as Helper
import "../Controls" as Controls

Item {
    id: root

    property int fix: -1
    property int eph: 0
    property int epv: 0
    property int satellitesVisible: 0
    property var coordinate: QtPositioning.coordinate()

    property color snsColor : {
        switch (fix) {
        case -1:
        case 0: return palette.disabledColor;
        case 1: return palette.negativeColor;
        case 2: return palette.neutralColor;
        case 3:
        default: return palette.textColor;
        }
    }

    implicitHeight: row.height

    RowLayout {
        id: row
        anchors.centerIn: parent
        width: parent.width

        ColumnLayout {
            id: column
            Layout.alignment: Qt.AlignLeft

            Controls.Label {
                color: snsColor
                font.pixelSize: root.width * 0.045
                font.bold: true
                text: qsTr("Lat.:") + Helper.degreesToDmsString(coordinate.latitude, false)
            }

            Controls.Label {
                color: snsColor
                font.pixelSize: root.width * 0.045
                font.bold: true
                text: qsTr("Lon.:") + Helper.degreesToDmsString(coordinate.longitude, true)
            }
        }

        Controls.ColoredIcon {
            color: snsColor
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
                color: snsColor
                font.pixelSize: root.width * 0.045
                font.bold: true
                text: qsTr("HDOP:") + eph
            }

            Controls.Label {
                color: snsColor
                font.pixelSize: root.width * 0.045
                font.bold: true
                text: qsTr("VDOP:") + epv
            }
        }
    }
}
