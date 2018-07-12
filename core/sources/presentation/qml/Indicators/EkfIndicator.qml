import QtQuick 2.6

import "../Controls" as Controls
import "qrc:/JS/helper.js" as Helper

Item {
    id: root

    property var bars: []
    property real caution: 0.5
    property real danger: 0.8

    implicitWidth: sizings.controlBaseSize
    implicitHeight: width

    Row {
        id: row
        spacing: root.width / 20
        anchors.centerIn: parent

        Repeater {
            id: repeater
            model: bars

             Rectangle {
                 width: root.width / repeater.count - row.spacing
                 height: root.height
                 radius: 2
                 color: customPalette.sunkenColor

                 Rectangle {
                     anchors.bottom: parent.bottom
                     width: parent.width
                     height: modelData <= 0 ? 0 : root.height * Math.min(modelData, 1.0)
                     radius: 1
                     color: {
                         if (modelData < caution) return customPalette.positiveColor;
                         if (modelData < danger) return customPalette.cautionColor;
                         return customPalette.dangerColor
                     }
                 }
             }
        }
    }
}

