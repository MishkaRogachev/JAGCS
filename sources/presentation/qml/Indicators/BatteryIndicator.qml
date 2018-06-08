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
            return customPalette.positiveColor;
        if (percentage > 15)
            return customPalette.cautionColor;
        if (percentage > 0)
            return customPalette.dangerColor;

        return customPalette.sunkenColor;
    }

    Item {
        id: fill
        anchors.fill: parent
        anchors.margins: root.width * 0.1
        anchors.topMargin: root.width * 0.33

        Text {
            id: textItem
            text: percentage
            font.pixelSize: fill.height * 0.75
            font.bold: true
            anchors.centerIn: parent
            color: root.color
        }

        Rectangle {
            anchors.bottom: parent.bottom
            width: parent.width
            height: fill.height * percentageBordered / 100
            color: root.color
            clip: true

            Text {
                text: textItem.text
                font.pixelSize: textItem.font.pixelSize
                font.bold: true
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom: parent.bottom
                anchors.bottomMargin: -1
                color: customPalette.raisedColor
            }
        }
    }
}
