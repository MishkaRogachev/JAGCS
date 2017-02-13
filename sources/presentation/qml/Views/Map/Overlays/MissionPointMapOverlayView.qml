import QtQuick 2.6
import QtLocation 5.6
import QtPositioning 5.6

import "qrc:/Controls"

MapItemView {
    delegate: MapQuickItem {
        coordinate: itemCoordinate
        anchorPoint.x: sourceItem.width / 2
        anchorPoint.y: sourceItem.height / 2
        z: 1

        sourceItem: Rectangle {
            width: palette.controlBaseSize
            height: width
            radius: width / 2
            color: palette.backgroundColor
            border.color: itemCurrent ? palette.highlightColor : palette.missionColor
            border.width: 4

            ColoredIcon {
                id: icon
                anchors.centerIn: parent
                source: itemIcon
                color: palette.textColor
                visible: itemIcon.length > 0
                width: parent.width * 0.6
                height: parent.height * 0.6
            }

            Label {
                visible: !icon.visible
                text: itemSeq
                color: palette.textColor
                anchors.centerIn: parent
                font.bold: true
            }
        }
    }
}
