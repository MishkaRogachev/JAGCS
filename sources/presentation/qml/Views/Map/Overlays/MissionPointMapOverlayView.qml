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
            width: 32 // TODO: map point size
            height: width
            radius: width / 2
            color: palette.missionColor

            Label {
                text: itemSeq
                anchors.centerIn: parent
                font.bold: true
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }
    }
}
