import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/JS/helper.js" as Helper
import "qrc:/Controls" as Controls

Controls.Label {
    id: root

    property var log

    text: "[" + Helper.formatTime(log.timestamp) + "] " + log.message
    color: {
        switch (log.type) {
        case LogMessage.Common: return palette.textColor;
        case LogMessage.Positive: return palette.positiveColor;
        case LogMessage.Warning: return palette.neutralColor;
        case LogMessage.Critical: return palette.negativeColor;
        }
    }
}
