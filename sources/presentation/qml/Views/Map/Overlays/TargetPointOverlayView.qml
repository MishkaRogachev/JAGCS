import QtQuick 2.6
import QtLocation 5.6
import QtPositioning 5.6

import "qrc:/Controls" as Control

MapItemView {
    id: root

    delegate: MapQuickItem {
        coordinate: targetPosition
        z: 2

        Behavior on coordinate {
            CoordinateAnimation { duration: 200 }
        }

        sourceItem: Item {

            Control.ColoredIcon {
                id: image
                anchors.centerIn: parent
                source: "qrc:/indicators/pick_aim.svg"
                color: palette.highlightColor
                width: palette.controlBaseSize
                height: width
            }

            Control.Label {
                text: vehicleId
                anchors.centerIn: parent
                font.pixelSize: image.width * 0.3
                font.bold: true
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }
    }
}
