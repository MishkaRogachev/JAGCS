import QtQuick 2.6
import QtLocation 5.6
import QtPositioning 5.6

import "qrc:/Controls"

MapItemView {
    delegate: MapQuickItem {

        property real directionAnimated: direction

        coordinate: position
        z: 1000

        Behavior on coordinate {
            CoordinateAnimation { duration: 200 }
        }

        Behavior on directionAnimated {
            RotationAnimation {
                duration: 200
                direction: RotationAnimation.Shortest
            }
        }

        Connections {
            target: map
            onTrackingVehicleChanged: tryCenterVehicle()
        }

        onCoordinateChanged: tryCenterVehicle()
        sourceItem: Item {

            Image {
                anchors.centerIn: parent
                rotation: directionAnimated - map.bearing
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
            if (!map.trackingVehicle || !isSelected) return;

            if (coordinate) map.center = coordinate;
            if (direction) map.bearing = directionAnimated;
        }
    }
}
