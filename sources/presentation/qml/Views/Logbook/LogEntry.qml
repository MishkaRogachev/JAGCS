import QtQuick 2.6
import JAGCS 1.0

import "qrc:/JS/helper.js" as Helper
import "qrc:/Controls" as Controls

Item {
    id: root

    property var log

    implicitHeight: Math.max(timestamp.height, container.height)

    Controls.Label {
        id: timestamp
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
        text: log ? "[" + Helper.formatTime(log.timestamp) + "]" : ""
        font.pixelSize: palette.fontPixelSize * 0.6
        font.bold: true
        color: label.color
    }

    Item {
        id: container
        width: root.width - timestamp.width - palette.spacing
        height: label.height
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        clip: true

        Controls.Label {
            id: label
            text: log ? log.message : ""
            font.pixelSize: palette.fontPixelSize * 0.6
            color: {
                if (!log) return palette.backgroundColor;

                switch (log.type) {
                case LogMessage.Common: return palette.textColor;
                case LogMessage.Positive: return palette.positiveColor;
                case LogMessage.Warning: return palette.neutralColor;
                case LogMessage.Critical: return palette.negativeColor;
                }
            }

            Timer {
                property int step: 1
                running: visible && (label.width - container.width) > 1
                onRunningChanged: label.x = 0
                repeat: true
                interval: 100
                onTriggered: {
                    label.x -= step;
                    if (label.x > 0) {
                        label.x = 0;
                        step = -step;
                    }
                    if (label.x <= container.width - label.width) {
                        step = -step;
                    }
                }
            }
        }
    }
}
