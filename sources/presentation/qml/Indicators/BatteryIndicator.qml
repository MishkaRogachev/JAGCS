import QtQuick 2.6
import QtQuick.Layouts 1.3

import "../Controls" as Controls

Controls.ColoredIcon {
    id: root

    property int percentage: -1
    readonly property int percentageBordered: Math.max(0, Math.min(percentage, 100))

    source: "qrc:/indicators/battery.svg"
    implicitWidth: sizings.controlBaseSize
    implicitHeight: width
    color: {
        if (percentage > 50)
            return palette.positiveColor;
        if (percentage > 15)
            return palette.cautionColor;
        if (percentage > 0)
            return palette.dangerColor;

        return palette.sunkenColor;
    }

    Text {
        id: textItem
        text: percentage// > -1 ? percentage : "-"
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
        height: (parent.height - 14) * percentageBordered / 100
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
