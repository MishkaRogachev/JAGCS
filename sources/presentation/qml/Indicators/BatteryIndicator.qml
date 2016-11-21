import QtQuick 2.6
import QtQuick.Layouts 1.3

import "../Controls"

ColoredIcon {
    id: root

    property int charge: -1

    source: "qrc:/icons/battery.svg"
    color: {
        if (charge > 50)
            return palette.positiveColor;
        if (charge > 15)
            return palette.neutralColor;
        if (charge > 0)
            return palette.negativeColor;

        return palette.disabledColor;
    }

    Text {
        id: textItem
        text: charge > -1 ? charge : "-"
        font.pixelSize: parent.height / 3
        font.bold: true
        anchors.centerIn: parent
        anchors.verticalCenterOffset: height / 4
        color: parent.color
    }

    Rectangle {
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 3
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width - 6
        height: charge > 0 ? (parent.height - 16) * charge / 100 : 0
        color: parent.color
        clip: true

        Text {
            text: textItem.text
            font.pixelSize: textItem.font.pixelSize
            font.bold: true
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: parent.anchors.bottomMargin
            color: palette.backgroundColor
        }
    }
}
