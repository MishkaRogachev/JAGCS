import QtQuick 2.6

import "../Controls"

ColoredIcon {
    id: root

    property int fix: -1
    property int satellitesVisible: -1

    source: "qrc:/icons/gps.svg"

    color: {
        switch (fix) {
        case 0: return palette.disabledColor;
        case 1: return palette.negativeColor;
        case 2: return palette.neutralColor;
        case 3: return palette.positiveColor;
        default: return palette.disabledColor;
        }
    }

    Text {
        text: satellitesVisible > -1 ? satellitesVisible : "-"
        font.pixelSize: parent.height / 4
        font.bold: true
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        color: parent.color
    }
}
