import QtQuick 2.6
import QtQuick.Controls 2.0

import "qrc:/Controls"

import "qrc:/JS/helper.js" as Helper

Item {
    id: root

    property color snsColor : {
        if (!vehicle) return palette.disabledColor;

        switch (vehicle.gps.fix) {
        case 0: return palette.disabledColor;
        case 1: return palette.negativeColor;
        case 2: return palette.neutralColor;
        case 3: return palette.textColor;
        default: return palette.disabledColor;
        }
    }

    height: column.height

    Column {
        id: column
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.leftMargin: palette.margins

        Label {
            anchors.left: parent.left
            color: snsColor
            font.pixelSize: root.width * 0.045
            font.bold: true
            text: qsTr("Lat.:") + (vehicle ? Helper.degreesToDmsString(
                     vehicle.gps.coordinate.latitude, false) : qsTr("None"))
        }

        Label {
            anchors.left: parent.left
            color: snsColor
            font.pixelSize: root.width * 0.045
            font.bold: true
            text: qsTr("Lon.:") + (vehicle ? Helper.degreesToDmsString(
                     vehicle.gps.coordinate.longitude, true) : qsTr("None"))
        }
    }

    Row {
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.rightMargin: palette.margins
        spacing: 5

        ColoredIcon {
            color: snsColor
            source: "qrc:/icons/gps.svg"
            height: column.height
            width: height

            Text {
                text: vehicle ? vehicle.gps.satellitesVisible : "-"
                font.pixelSize: parent.height / 4
                font.bold: true
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                color: parent.color
            }
        }

        Column {
            anchors.verticalCenter: parent.verticalCenter

            Label {
                anchors.right: parent.right
                color: snsColor
                font.pixelSize: root.width * 0.045
                font.bold: true
                text: qsTr("HDOP:") + (vehicle ? vehicle.gps.eph : qsTr("None"))
            }

            Label {
                anchors.right: parent.right
                color: snsColor
                font.pixelSize: root.width * 0.045
                font.bold: true
                text: qsTr("VDOP:") + (vehicle ? vehicle.gps.epv : qsTr("None"))
            }
        }
    }
}
