import QtQuick 2.6
import QtLocation 5.6
import QtPositioning 5.6

import "qrc:/Controls" as Controls
import "qrc:/Indicators" as Indicators

MapItemView {
    delegate: MapQuickItem {

        property real headingAnimated: heading
        property real courseAnimated: course

        coordinate: position
        z: 1000

        Behavior on coordinate {
            CoordinateAnimation { duration: 200 }
        }

        Behavior on headingAnimated {
            RotationAnimation {
                duration: 200
                direction: RotationAnimation.Shortest
            }
        }

        Behavior on courseAnimated {
            RotationAnimation {
                duration: 200
                direction: RotationAnimation.Shortest
            }
        }

        Connections {
            target: map
            onTrackingVehicleChanged: tryCenterVehicle()
            onCenterChanged: tryCenterVehicle()
        }

        onCoordinateChanged: tryCenterVehicle()
        sourceItem: Item {

            Indicators.SpeedArrow {
                anchors.centerIn: parent
                fix: snsFix
                rotation: courseAnimated - map.bearing
                speed: groundspeed
                visible: groundspeed > 0.1
                width: palette.controlBaseSize * 4
                height: width
            }

            Image {
                anchors.centerIn: parent
                rotation: headingAnimated - map.bearing
                source: mark
                width: palette.controlBaseSize * 3
                height: width
            }

            Controls.Label {
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
            map.bearing = headingAnimated;
        }
    }
}
