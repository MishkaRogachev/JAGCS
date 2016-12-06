import QtQuick 2.6
import QtLocation 5.6
import QtPositioning 5.6

import "qrc:/Controls"

MapItemView {
    delegate: MapQuickItem {
        coordinate: position
        z: 2

        Behavior on coordinate {
            CoordinateAnimation { duration: 200 }
        }

        sourceItem: Item {

            Image {
                anchors.centerIn: parent
                rotation: direction
                source: mark
            }

            Label {
                text: vehicleId
                anchors.centerIn: parent
                font.bold: true
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }
    }
}
