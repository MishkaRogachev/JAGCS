import QtQuick 2.6
import QtLocation 5.6
import QtPositioning 5.6

import "qrc:/Controls"

MapItemView {
    id: root

    delegate: MapQuickItem {
        coordinate: homePosition
        z: 2

        Behavior on coordinate {
            CoordinateAnimation { duration: 200 }
        }

        sourceItem: Item {

            Image {
                id: image
                anchors.centerIn: parent
                source: "qrc:/indicators/home_map_mark.svg"
                width: palette.controlBaseSize
                height: width
            }

            Label {
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
