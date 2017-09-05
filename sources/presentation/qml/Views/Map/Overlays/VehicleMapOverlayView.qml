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

        Connections {
            target: map
            onTrackingVehicleChanged: tryCenterVehicle()
        }

        onCoordinateChanged: tryCenterVehicle()
        sourceItem: Item {

            Image {
                anchors.centerIn: parent
                rotation: direction
                source: mark
                width: palette.controlBaseSize * 3
                height: width
            }

            Label {
                text: vehicleId
                anchors.centerIn: parent
                font.bold: true
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }

        function tryCenterVehicle() {
            if (map.trackingVehicle && isSelected && coordinate) map.center = coordinate
        }
    }
}
