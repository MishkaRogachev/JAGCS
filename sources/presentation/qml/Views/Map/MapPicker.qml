import QtQuick 2.6
import QtLocation 5.6
import QtPositioning 5.6

import "qrc:/Controls" as Controls

MapQuickItem {
    id: root
    anchorPoint.x: sourceItem.width / 2
    anchorPoint.y: sourceItem.height / 2

    sourceItem: Controls.ColoredIcon {
        width: sizings.controlBaseSize
        height: width
        source: "qrc:/indicators/pick_aim.svg"
        color: customPalette.activeMissionColor
    }
}
