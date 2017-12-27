import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/JS/helper.js" as Helper
import "qrc:/Controls" as Controls

RowLayout {
    id: logView

    property var log

    Controls.Label {
        id: timestamp
        anchors.verticalCenter: parent.verticalCenter
        text: log ? "[" + Helper.formatTime(log.timestamp) + "]" : ""
        font.pixelSize: sizings.fontPixelSize * 0.6
        font.bold: true
        color: label.color
    }

    Controls.Label {
        id: label
        text: log ? log.message : ""
        font.pixelSize: sizings.fontPixelSize * 0.6
        color: {
            if (!log) return palette.backgroundColor;

            switch (log.type) {
            case LogMessage.Common: return palette.textColor;
            case LogMessage.Positive: return palette.positiveColor;
            case LogMessage.Warning: return palette.cautionColor;
            case LogMessage.Critical: return palette.dangerColor;
            }
        }
    }
}
