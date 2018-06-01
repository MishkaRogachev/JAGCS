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
            onTrackingVehicleIdChanged: tryCenterVehicle()
            onCenterChanged: tryCenterVehicle()
        }

        onCoordinateChanged: tryCenterVehicle()
        sourceItem: Item {
            rotation: -map.bearing
            opacity: vehicleOnline ? 1 : 0.5

            Indicators.SpeedArrow {
                anchors.centerIn: parent
                fix: snsFix
                rotation: courseAnimated
                speed: groundspeed
                visible: groundspeed > 0.1
                width: sizings.controlBaseSize * 4
                height: width
            }

            Image {
                anchors.centerIn: parent
                rotation: headingAnimated
                source: translator.imageFromVehicleType(vehicleType)
                width: sizings.controlBaseSize * 3
                height: width
            }

            Controls.Label {
                text: vehicleName
                anchors.top: parent.bottom
                anchors.left: parent.right
                anchors.margins: sizings.controlBaseSize
                rotation: map.bearing
                font.pixelSize: sizings.secondaryFontSize
                font.bold: true
            }
        }

        function tryCenterVehicle() {
            if (map.trackingVehicleId != vehicleId) return;

            if (coordinate) map.setCenterOffsetted(coordinate);
            if (map.trackYaw) map.bearing = headingAnimated;
        }
    }
}
